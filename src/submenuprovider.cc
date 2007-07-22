#include "submenuprovider.h"
#include <vdr/plugin.h>

MainMenuItemsList* SubMenuProvider::MainMenuItems()
{
    ResetMainMenuItemsList();
    
    
    _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem("A custom sub menu", osUser1)));
//    _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Schedule"), osSchedule)));
//    _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
//    _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Timers"), osTimers)));
//    _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Recordings"), osRecordings)));

    for (int i = 0; ; i++) {
      cPlugin *p = cPluginManager::GetPlugin(i);
      if (p) {
         const char *item = p->MainMenuEntry();
         if (item)
            _osdItems.push_back(MainMenuItem::CreatePluginMenuItem(item, i));
         }
      else
         break;
      }

    _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Setup"), osSetup)));

    if (Commands.Count())
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Commands"), osCommands)));

    return &_osdItems;
}

void SubMenuProvider::ResetMainMenuItemsList()
{
    for( MainMenuItemsList::iterator i = _osdItems.begin(); i != _osdItems.end(); i++)
    {
       delete *i;
    }
    _osdItems.clear(); 
}

cOsdMenu* SubMenuProvider::OpenSubMenu(int mainMenuItemIndex)
{
    if (mainMenuItemIndex == 0)
    {
        cOsdMenu* fooMenu = new cOsdMenu("Foo-Submenu");
        fooMenu->Add(new cOsdItem(tr("Schedule"), osSchedule));
        fooMenu->Add(new cOsdItem(tr("Channels"), osChannels));
        fooMenu->Add(new cOsdItem(tr("Timers"), osTimers));
        fooMenu->Add(new cOsdItem(tr("Recordings"), osRecordings));
        return fooMenu;
    }
    
    return NULL;
}
