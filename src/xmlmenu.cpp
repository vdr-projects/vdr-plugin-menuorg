#include <libxml++/libxml++.h>
#include <vdr/plugin.h>
#include "menunode.h"
#include "vdrmenuitem.h"
#include "submenuitem.h"
#include "pluginmenuitem.h"
#include "xmlmenu.h"
#include <iostream>

using namespace xmlpp;
using namespace std;

void XmlMenu::loadXmlMenu()
{ 
	// TODO: show how vdr handels the path vars (developer doc)
	// and change code for dynamic path vars
	const char *File = "/var/lib/vdr/plugins/vdr-menu.xml";

	try
	{
		DomParser parser;

		//TODO: patch the xmlfile with the xsd definition for validate the schema
		//parser.set_validate();
		parser.set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
		parser.parse_file(File);
		if(parser)
		{
			//Walk the tree:
			MenuCount=0;
			const Element* rootElement = parser.get_document()->get_root_node(); //deleted by DomParser.
			parseNode(rootElement, &_rootMenuNode);
		}
	}
	catch(const std::exception& ex)
	{
		//TODO: print output to syslog (isyslog or dsyslog?)
		cout << "Exception caught: " << ex.what() << endl;

		//TODO: display message on osd
	}
}

void XmlMenu::parseNode(const Element* element, MenuNode* menuNode)
{
    
    Node::NodeList children = element->get_children();
    for (Node::NodeList::iterator i = children.begin(); i != children.end(); i++)
    {
        const xmlpp::Element* childElement = dynamic_cast<const xmlpp::Element*>(*i);
    
        if (childElement)
        {
            if (childElement->get_name() == "menu")
            {
                if (const xmlpp::Attribute* nameAttribute = childElement->get_attribute("name"))
                {
                    MenuNode* subMenu = menuNode->AddChild(new SubMenuItem(nameAttribute->get_value().c_str()));
                    parseNode(childElement, subMenu);
                }
            }
            if (childElement->get_name() == "system")
            {
                if (const xmlpp::Attribute* nameAttribute = childElement->get_attribute("name"))
                {
                    const char* systemMenuItemText = nameAttribute->get_value().c_str();
                    MenuNode* systemMenuItem = menuNode->AddChild(
                      new VdrMenuItem(systemMenuItemText, geteOSState(systemMenuItemText)));
                }
            }
            if (childElement->get_name() == "plugin")
            {
                if (const xmlpp::Attribute* nameAttribute = childElement->get_attribute("name"))
                {
                    const char* pluginMainMenuEntry;
                    int pluginIndex;
                    
                    if (FindPluginByName(nameAttribute->get_value(), &pluginMainMenuEntry, pluginIndex))
                    {
                        MenuNode* pluginMenuItem = menuNode->AddChild(
                          new PluginMenuItem(pluginMainMenuEntry, pluginIndex));
                    }
                }
            }
        }
    }
}
/*
enum eOSState { osUnknown,
                osContinue,
                osSchedule,
                osChannels,
                osTimers,
                osRecordings,
                osPlugin,
                osSetup,
                osCommands,
                osPause,
                osRecord,
                osReplay,
                osStopRecord,
                osStopReplay,
                osCancelEdit,
                osSwitchDvb,
                osBack,
                osEnd,
                os_User, // the following values can be used locally
                osUser1,
                osUser2,
                osUser3,
                osUser4,
                osUser5,
                osUser6,
                osUser7,
                osUser8,
                osUser9,
                osUser10,
              };
*/
eOSState XmlMenu::geteOSState(const Glib::ustring& name)
{
	if(name == "Continue")
	{
		return osContinue;	
	}
	else if (name == "Schedule")
	{
		return osSchedule;
	}
	else if (name == "Channels")
	{
		return osChannels;
	}
	else if (name == "Timers")
	{
		return osTimers;
	}
	else if (name == "Recordings")
	{
		return osRecordings;
	}
	else if (name == "Plugin")
	{
		return osPlugin;
	}
	else if (name == "Setup")
	{
		return osSetup;
	}
	else if (name == "Pause")
	{
		return osPause;
	}
	else if (name == "Record")
	{
		return osRecord;
	}
	else if (name == "Replay")
	{
		return osReplay;
	}
	else if (name == "CancelEdit")
	{
		return osCancelEdit;
	}
	else if (name == "SwitchDvb")
	{
		return osSwitchDvb;
	}
	else if (name == "Back")
	{
		return osBack;
	}
	else if (name == "End")
	{
		return osEnd;
	}
	else if (name == "User")
	{
		return os_User;
	}
	else if (name == "Commands")
	{
		return osCommands;
	}
	else
		return osContinue;
}

bool XmlMenu::FindPluginByName(std::string name, const char** mainMenuEntry,
  int& pluginIndex)
{
    int i=0;
    while (cPlugin *p = cPluginManager::GetPlugin(i))
    {
        if (name == p->Name()) 
        {
            if (const char *item = p->MainMenuEntry())
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
