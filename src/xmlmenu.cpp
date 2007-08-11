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
        parser.parse_file(menuFileName);
        

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
