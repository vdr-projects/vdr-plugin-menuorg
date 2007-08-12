/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (C) 2007 Thomas Creutz, Tobias Grimm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id:$
 *
 */

#include "xmlmenu.h"
#include <iostream>
#include <libxml++/libxml++.h>
#include <exception>
#include <vdr/plugin.h>
#include "vdrmenuitem.h"
#include "submenuitem.h"
#include "pluginmenuitem.h"

using namespace xmlpp;
using namespace std;

MenuNode* XmlMenu::LoadXmlMenu(string menuFileName)
{ 
    MenuNode* menuRoot = new MenuNode();

    try
    {
        DomParser parser;

        //TODO: patch the xmlfile with the xsd definition for validate the schema
        //parser.set_validate();
        parser.set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
//        parser.parse_file(menuFileName);
        parser.parse_file("/var/lib/vdr/plugins/menuorg.xml");

        //DtdValidator validator( dtdFileName );
        DtdValidator validator( "/var/lib/vdr/plugins/menuorg.dtd" );
        Document *pDoc = parser.get_document();
        validator.validate( pDoc );

        const Element* rootElement = parser.get_document()->get_root_node();
        ParseElement(rootElement, menuRoot);
    }
    catch(const std::exception& ex)
    {
        delete menuRoot;
        menuRoot = NULL;

        //TODO: print output to syslog (isyslog or dsyslog?)
        cout << "Exception caught: " << ex.what() << endl;
        isyslog("Exception caught: %s", ex.what());
        //TODO: display message on osd
    }
/*
    catch(const xmlpp::parse_error& ex)
    {
        // DTD or document is not well-formed
        delete menuRoot;
        menuRoot = NULL;
    }
    catch (const xmlpp::validation_error& ex)
    {
        // document is not valid
        delete menuRoot;
        menuRoot = NULL;
    }*/
    return menuRoot;
}

void XmlMenu::ParseElement(const Element* element, MenuNode* menuNode)
{
    Node::NodeList children = element->get_children();
    for (Node::NodeList::iterator i = children.begin(); i != children.end(); i++)
    {
        const xmlpp::Element* childElement = dynamic_cast<const xmlpp::Element*>(*i);

        if (childElement)
        {
            const xmlpp::Attribute* nameAttribute = childElement->get_attribute("name");

            if (nameAttribute)
            {
                string type = childElement->get_name();
                string name = nameAttribute->get_value();

                if ( type == "menu")
                {
                    MenuNode* subMenu = AddSubMenuItem(name, menuNode);
                    ParseElement(childElement, subMenu);
                }
                else if (type == "system")
                {
                    AddSystemMenuItem(name, menuNode);
                }
                else if (type == "plugin")
                {
                    AddPluginMenuItem(name, menuNode);
                }
            }
        }
    }
}

MenuNode* XmlMenu::AddSubMenuItem(string name, MenuNode* menu)
{
    return menu->AddChild(new SubMenuItem(name));
}

void XmlMenu::AddSystemMenuItem(string name, MenuNode* menu)
{
    menu->AddChild(new VdrMenuItem(name, MenuTextToVdrState(name)));
}

void XmlMenu::AddPluginMenuItem(string pluginName, MenuNode* menu)
{
    const char* pluginMainMenuEntry;
    int pluginIndex;

    if (FindPluginByName(pluginName, &pluginMainMenuEntry, pluginIndex))
    {
        menu->AddChild(new PluginMenuItem(pluginMainMenuEntry, pluginIndex));
    }
}

eOSState XmlMenu::MenuTextToVdrState(string menuText)
{
    if (menuText == "Schedule")
    {
        return osSchedule;
    }
    else if (menuText == "Channels")
    {
        return osChannels;
    }
    else if (menuText == "Timers")
    {
        return osTimers;
    }
    else if (menuText == "Recordings")
    {
        return osRecordings;
    }
    else if (menuText == "Setup")
    {
        return osSetup;
    }
    else if (menuText == "Commands")
    {
        return osCommands;
    }
    else
        return osContinue;
}

bool XmlMenu::FindPluginByName(string name, const char** mainMenuEntry, int& pluginIndex)
{
    int i = 0;

    while (cPlugin *plugin = cPluginManager::GetPlugin(i))
    {
        if (name == plugin->Name()) 
        {
            if (const char *item = plugin->MainMenuEntry())
            {
                pluginIndex = i;
                *mainMenuEntry = item;
                return true;
            }
        }
        i++;
    }
    return false;
}
