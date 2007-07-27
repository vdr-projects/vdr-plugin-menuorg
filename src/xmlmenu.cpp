#include <libxml++/libxml++.h>
#include <vdr/plugin.h>
#include "menunode.h"
#include "vdrmenuitem.h"
#include "submenuitem.h"
#include "pluginmenuitem.h"
#include "xmlmenu.h"
#include <iostream>

//#include <vdr/submenupatch.h>
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

		//TODO: patch the xmlfile with the xsd definition for validate
		//parser.set_validate();
		parser.set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
		parser.parse_file(File);
		if(parser)
		{
			//Walk the tree:
			const Node* pNode = parser.get_document()->get_root_node(); //deleted by DomParser.
			parseNode(pNode,0,NULL);
		}
	}
	catch(const std::exception& ex)
	{
		//TODO: print output to syslog (isyslog or dsyslog?)
		cout << "Exception caught: " << ex.what() << endl;

		//TODO: display message on osd
	}
}

void XmlMenu::parseNode(const Node* a_node, unsigned int Parent, MenuNode *parentNode)
{
	const ContentNode*  nodeContent = dynamic_cast<const ContentNode*>(a_node);
	const TextNode*     nodeText    = dynamic_cast<const TextNode*>(a_node);
	const CommentNode*  nodeComment = dynamic_cast<const CommentNode*>(a_node);
	MenuNode newparentNode;

/****
    MenuNode* subMenu1 =_rootMenuNode.AddChild(new SubMenuItem("Custom menu 1"));
        subMenu1->AddChild(new VdrMenuItem(tr("Schedule"), osSchedule));
        subMenu1->AddChild(new VdrMenuItem(tr("Channels"), osChannels));
        MenuNode* subMenu1_1 = subMenu1->AddChild(new SubMenuItem("Custom menu 1.1"));
            subMenu1_1->AddChild(new VdrMenuItem(tr("Timers"), osTimers));
            subMenu1_1->AddChild(new VdrMenuItem(tr("Recordings"), osRecordings));
     MenuNode* subMenu2 =_rootMenuNode.AddChild(new SubMenuItem("Custom menu 2"));
 subMenu2->AddChild(new PluginMenuItem(item, i));
****/

	Glib::ustring nodename = a_node->get_name();

	if(!nodeText && !nodeComment && !nodename.empty()) //Let's not say "name: text".
	{
		/*
		for(unsigned int i=0;i<=Parent;i++)
		{
			printf("  ");
		}*/
		if (nodename == "menus")
		{
			//cout << Parent << "-" << MainMenuIndex << "-" << myMenuNr << "-ROOT" << endl;

		}
		else if (nodename == "system")
		{
			if (const Element* nodeElement = dynamic_cast<const Element*>(a_node))
			{
				const Element::AttributeList& attributes = nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
				{
					const Attribute* attribute = *iter;
					//cout << Parent << "-" << MainMenuIndex << "-" << myMenuNr << "-SystemItem=" << attribute->get_value()  << endl;
					if (parentNode == NULL)
						newparentNode =_rootMenuNode.AddChild(new VdrMenuItem(tr((const char*) attribute->get_value()), geteOSState(attribute->get_value())));
					else
						newparentNode = parentNode->AddChild(new VdrMenuItem(tr((const char*) attribute->get_value()), geteOSState(attribute->get_value())));
				}
			}
		}
		else if (nodename == "menu")
		{
			if (const Element* nodeElement = dynamic_cast<const Element*>(a_node))
			{
				const Element::AttributeList& attributes = nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
				{
					const Attribute* attribute = *iter;
					//cout << Parent << "-" << MainMenuIndex << "-" << myMenuNr << "-MenuItem=" << attribute->get_value()  << endl;
					if (parentNode == NULL)
						newparentNode =_rootMenuNode.AddChild(new SubMenuItem((const char*) attribute->get_value()));
					else
						newparentNode = parentNode->AddChild(new SubMenuItem((const char*) attribute->get_value()));
				}				
			}
		}
		else if (nodename == "plugin")
		{
			if (const Element* nodeElement = dynamic_cast<const Element*>(a_node))
			{
				const Element::AttributeList& attributes = nodeElement->get_attributes();
				for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
				{
					const Attribute* attribute = *iter;
					//cout << Parent << "-" << MainMenuIndex << "-" << myMenuNr << "-PluginItem=" << attribute->get_value()  << endl;
					if (getPluginIndex(attribute->get_value()) != NULL)
					{
						PluginItemAndIndex myPlugin = getPluginIndex(attribute->get_value());
						if (parentNode == NULL)
							newparentNode =_rootMenuNode.AddChild(new PluginMenuItem(myPlugin.item, myPlugin.index));
						else
							newparentNode = parentNode->AddChild(new PluginMenuItem(myPlugin.item, myPlugin.index));
					}
				}
				//subMenu2->AddChild(new PluginMenuItem(item, i));
			}
		}
	}
	if(!nodeContent)
	{
		//Recurse through child nodes:
		Node::NodeList list = a_node->get_children();
		for(Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
		{
			parseNode(*iter, Parent+1, newparentNode); //recursive
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
	else
		return osContinue;
}

PluginItemAndIndex XmlMenu::getPlugin(const Glib::ustring& name)
{
	PluginItemAndIndex returnVar;
/*
	returnVar.item = NULL;
	returnVar.index = NULL;
*/
	int i=0;
	while (cPlugin *p = cPluginManager::GetPlugin(i))
	{
		if (const char *item = p->MainMenuEntry())
		{
			if (name == (const Glib::ustring) p->Name())
				returnVar.item = item;
				returnVar.index = i;
				break;
		}
		i++;
	}
	return returnVar;
}
