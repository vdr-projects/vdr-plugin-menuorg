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
 * $Id$
 *
 */

#include "menuconfiguration.h"
#include <libxml++/libxml++.h>
#include <exception>
#include <iostream>
#include <vdr/plugin.h>
#include <glibmm/convert.h>
#include "systemmenunode.h"
#include "submenunode.h"
#include "pluginmenunode.h"
#include "commandmenunode.h"

using namespace xmlpp;
using namespace std;

const string MenuConfiguration::_dtd = 
  "<!ELEMENT menus ((menu | system | plugin | command)+)>\n"
  "<!ELEMENT menu ((menu | system | plugin | command)+)>\n"
  "<!ATTLIST menu name CDATA #REQUIRED>\n"
  "<!ELEMENT system EMPTY>\n"
  "<!ATTLIST system\n"
  " name CDATA #REQUIRED\n"
  " title CDATA #IMPLIED>\n"
  "<!ELEMENT plugin EMPTY>\n"
  "<!ATTLIST plugin\n"
  " name CDATA #REQUIRED\n"
  " title CDATA #IMPLIED>\n"
  "<!ELEMENT command EMPTY>\n"
  "<!ATTLIST command\n"
  " name CDATA #REQUIRED\n"
  " execute CDATA #REQUIRED\n"
  " confirm (yes|no) #IMPLIED>";

MenuNode* MenuConfiguration::LoadMenu(string menuFileName)
{ 
    MenuNode* menuRoot = new MenuNode();

    try
    {
        dsyslog("loading menuorg config file from %s", menuFileName.c_str());

        DomParser parser;
        parser.set_substitute_entities();
        parser.parse_file(menuFileName);

        DtdValidator validator;
        validator.parse_memory(_dtd);

        Document *pDoc = parser.get_document();
        validator.validate( pDoc );

        const Element* rootElement = parser.get_document()->get_root_node();
        ParseElement(rootElement, menuRoot);

        AddUnconfiguredPlugins(menuRoot);
    }
    catch(const std::exception& ex)
    {
        delete menuRoot;
        menuRoot = NULL;

        cerr << "menuorg: Exception caught when parsing xml configuration: " << ex.what();
        esyslog("Exception caught when parsing xml configuration. See stderr output for details.");
    }

    return menuRoot;
}

void MenuConfiguration::ParseElement(const Element* element, MenuNode* menuNode)
{
    Node::NodeList children = element->get_children();
    for (Node::NodeList::iterator i = children.begin(); i != children.end(); i++)
    {
        const xmlpp::Element* childElement = dynamic_cast<const xmlpp::Element*>(*i);

        if (childElement)
        {
            const xmlpp::Attribute* nameAttribute = childElement->get_attribute("name");

            string type = childElement->get_name();
            string name = UnicodeToLocaleOrIso8859(nameAttribute->get_value());

            if ( type == "menu")
            {
                MenuNode* subMenu = AddSubMenuNode(name, menuNode);
                ParseElement(childElement, subMenu);
            }
            else if (type == "system")
            {
                const xmlpp::Attribute* titleAttribute = childElement->get_attribute("title");
                name = titleAttribute ? (string) UnicodeToLocaleOrIso8859(titleAttribute->get_value()) : name;
                AddSystemMenuNode(name, menuNode);
            }
            else if (type == "plugin")
            {
                const xmlpp::Attribute* titleAttribute = childElement->get_attribute("title");
                string title = titleAttribute ? (string) UnicodeToLocaleOrIso8859(titleAttribute->get_value()) : name;
                AddPluginMenuNode(name, menuNode, title);
            }
            else if (type == "command")
            {
                string execute = childElement->get_attribute("execute")->get_value();
                const xmlpp::Attribute* confirmAttribute = childElement->get_attribute("confirm");
                bool confirm = confirmAttribute ? (confirmAttribute->get_value() == "yes") : false;
                AddCommandMenuNode(name, execute, confirm, menuNode);
            }
        }
    }
}

MenuNode* MenuConfiguration::AddSubMenuNode(string name, MenuNode* menu)
{
    return menu->AddChild(new SubMenuNode(name));
}

void MenuConfiguration::AddSystemMenuNode(string name, MenuNode* menu)
{
    menu->AddChild(new SystemMenuNode(name, MenuTextToVdrState(name)));
}

void MenuConfiguration::AddPluginMenuNode(string pluginName, MenuNode* menu, string title)
{
    int pluginIndex;
    cPlugin* plugin;

    if (FindPluginByName(pluginName, plugin, pluginIndex))
    {
        _configuredPlugins.push_back(pluginName);
        menu->AddChild(new PluginMenuNode(plugin, pluginIndex, title));
    }
}

eOSState MenuConfiguration::MenuTextToVdrState(string menuText)
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

bool MenuConfiguration::FindPluginByName(string name, cPlugin*& plugin, int& pluginIndex)
{
    int i = 0;

    while (cPlugin *currentPlugin = cPluginManager::GetPlugin(i))
    {
        if (name == currentPlugin->Name()) 
        {
            plugin = currentPlugin;
            pluginIndex = i;
            return true;
        }
        i++;
    }

    return false;
}

void MenuConfiguration::AddUnconfiguredPlugins(MenuNode* menu)
{
    int i = 0;

    while (cPlugin *plugin = cPluginManager::GetPlugin(i))
    {
        if (find(_configuredPlugins.begin(), _configuredPlugins.end(), plugin->Name()) == _configuredPlugins.end())
        {
            menu->AddChild(new PluginMenuNode(plugin, i));
        }
        i++;
    }
}

void MenuConfiguration::AddCommandMenuNode(string name, string command, bool confirm, MenuNode* menu)
{
    menu->AddChild(new CommandMenuNode(name, command, confirm));
}

string MenuConfiguration::UnicodeToLocaleOrIso8859(Glib::ustring unicodeString)
{
    try
    {
        return Glib::locale_from_utf8(unicodeString);
    }
    catch (Glib::ConvertError)
    {
        return Glib::convert_with_fallback(unicodeString, "ISO8859-2", "UTF-8");
    }
}
