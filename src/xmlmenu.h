#ifndef ___XMLMENU_H
#define ___XMLMENU_H

#include "menunode.h"

class XmlMenu
{
	private:
		//void createMenu(); // create the Menu Node
		void parseNode(const Node *a_node, unsigned int Parent);
		eOSState geteOSState(char* name); // gets the eOSState for the given string
		int getPluginIndex(char* name); // gets the plugin index for the given string
	public:
		MenuNode _rootMenuNode; // hold the Menue Node
		XmlMenu (void);
		void loadXmlMenu(); // load the xmlfile
};

#endif 
