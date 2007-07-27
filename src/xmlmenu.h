#ifndef ___XMLMENU_H
#define ___XMLMENU_H

#include <libxml++/libxml++.h>
#include "menunode.h"

using namespace xmlpp;

class XmlMenu
{
	private:
		//void createMenu(); // create the Menu Node
		void ParseElement(const Element* a_node, MenuNode* menuNode);
		eOSState geteOSState(std::string name); // gets the eOSState for the given string
		bool FindPluginByName(std::string name, const char** mainMenuEntry, int& pluginIndex); // gets the plugin for the given string
		MenuNode* _subMenu[30]; // holds the submenus
		int MenuCount;

	public:
		MenuNode _rootMenuNode; // hold the Menue Nodes
		void loadXmlMenu(); // load the xmlfile
};

#endif 
