#include "menuorg.h"

extern "C" void *VDRPluginCreator()
{
    MenuOrgPlugin* plugin = new MenuOrgPlugin();
    return plugin;
}
