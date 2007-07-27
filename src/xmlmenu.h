#ifndef ___XMLMENU_H
#define ___XMLMENU_H

#include <libxml++/libxml++.h>
#include <iostream>
#include "menunode.h"

using namespace xmlpp;

struct PluginItemAndIndex
{
	const char* item;
	int index;
};

class XmlMenu
{
	private:
		//void createMenu(); // create the Menu Node
		void parseNode(const Node* a_node, unsigned int Parent, MenuNode *parentNode);
		eOSState geteOSState(const Glib::ustring& name); // gets the eOSState for the given string
		PluginItemAndIndex getPlugin(const Glib::ustring& name); // gets the plugin for the given string
	public:
		MenuNode _rootMenuNode; // hold the Menue Nodes
		void loadXmlMenu(); // load the xmlfile
};

#endif 
