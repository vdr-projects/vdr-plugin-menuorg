#include "submenuprovider.h"
#include <vdr/plugin.h>

SubMenuProvider::SubMenuProvider()
{
    _inSubMenu = false;
}

MainMenuItemsList* SubMenuProvider::MainMenuItems()
{
    ResetMainMenuItemsList();
    
    if (_inSubMenu)
    {
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Schedule"), osSchedule)));
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Timers"), osTimers)));
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Recordings"), osRecordings)));
    }
    else
    {
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem("A custom sub menu", osUser1)));
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem("Another custom sub menu", osContinue)));
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
    }

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

void SubMenuProvider::EnterSubMenu(int mainMenuItemIndex)
{
    if ((mainMenuItemIndex == 0) && !_inSubMenu)
    {
       _inSubMenu = true;
    }
}

bool SubMenuProvider::LeaveSubMenu()
{
    if (_inSubMenu)
    {
        _inSubMenu = false;
        return true;
    }
    else
    {
        return false;
    }
}
