#ifndef ___PLUGINMENUITEM_H
#define ___PLUGINMENUITEM_H

#include "menunode.h"
#include <vdr/osdbase.h>
#include <vdr/submenupatch.h>

class PluginMenuItem: public MenuNode
{
    private:
        const char* _pluginMainMenuEntry;
        int _pluginIndex;

    public:
        PluginMenuItem(const char* pluginMainMenuEntry, int pluginIndex);
        SubMenuPatch::MainMenuItem* CreateMainMenuItem();
};

#endif
