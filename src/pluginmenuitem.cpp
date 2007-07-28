#include "pluginmenuitem.h"
#include <vdr/submenupatch.h>

PluginMenuItem::PluginMenuItem(const char* pluginMainMenuEntry, int pluginIndex)
{
    _pluginMainMenuEntry = pluginMainMenuEntry;
    _pluginIndex = pluginIndex;
}

SubMenuPatch::MainMenuItem* PluginMenuItem::CreateMainMenuItem()
{
    return SubMenuPatch::MainMenuItem::CreatePluginMenuItem(
      _pluginMainMenuEntry, _pluginIndex);
}
