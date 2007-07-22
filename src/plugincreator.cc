#include "submenuplugin.h"

extern "C" void *VDRPluginCreator()
{
    SubMenuPlugin* plugin = new SubMenuPlugin();
    return plugin;
}
