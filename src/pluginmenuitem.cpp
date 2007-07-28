#include "pluginmenuitem.h"
#include <vdr/submenupatch.h>
#include "pluginmainmenuitem.h"

PluginMenuItem::PluginMenuItem(const char* pluginMainMenuEntry, int pluginIndex)
{
    _pluginMainMenuEntry = pluginMainMenuEntry;
    _pluginIndex = pluginIndex;
}

SubMenuPatch::IMainMenuItem* PluginMenuItem::CreateMainMenuItem()
{
    return new PluginMainMenuItem(_pluginMainMenuEntry, _pluginIndex);
}
