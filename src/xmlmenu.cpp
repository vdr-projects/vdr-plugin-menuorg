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
			ParseElement(rootElement, &_rootMenuNode);
		}
	}
	catch(const std::exception& ex)
	{
		//TODO: print output to syslog (isyslog or dsyslog?)
		cout << "Exception caught: " << ex.what() << endl;

		//TODO: display message on osd
	}
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
                if (childElement->get_name() == "menu")
                {
                    MenuNode* subMenu = menuNode->AddChild(new SubMenuItem(nameAttribute->get_value()));
                    ParseElement(childElement, subMenu);
                }
                else if (childElement->get_name() == "system")
                {
                    std::string systemMenuItemText = nameAttribute->get_value();
                    menuNode->AddChild(new VdrMenuItem(systemMenuItemText, geteOSState(systemMenuItemText)));
                }
                else if (childElement->get_name() == "plugin")
                {
                    const char* pluginMainMenuEntry;
                    int pluginIndex;
                    
                    if (FindPluginByName(nameAttribute->get_value(), &pluginMainMenuEntry, pluginIndex))
                    {
                        menuNode->AddChild(new PluginMenuItem(pluginMainMenuEntry, pluginIndex));
                    }
                }
            }
        }
    }
}

eOSState XmlMenu::geteOSState(std::string name)
{
	if (name == "Schedule")
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
	else if (name == "Setup")
	{
		return osSetup;
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
