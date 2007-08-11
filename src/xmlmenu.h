#ifndef ___XMLMENU_H
#define ___XMLMENU_H

#include <string>
#include <vdr/osdbase.h>
#include "menunode.h"

namespace xmlpp { class Element; }

class XmlMenu
{
    public:
        MenuNode* LoadXmlMenu();

    private:
        void ParseElement(const xmlpp::Element* a_node, MenuNode* menuNode);
        eOSState MenuTextToVdrState(std::string menuText);
        bool FindPluginByName(std::string name, const char** mainMenuEntry, int& pluginIndex);
        MenuNode* AddSubMenuItem(std::string name, MenuNode* menu);
        void AddSystemMenuItem(std::string name, MenuNode* menu);
        void AddPluginMenuItem(std::string pluginName, MenuNode* menu);
};

#endif 
