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
        _subMenuItem = new cOsdItem("A custom sub menu\t1xxx", osUser1);
        _osdItems.push_back(MainMenuItem::CreateCustomMenuItem(_subMenuItem));
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

void SubMenuProvider::EnterSubMenu(cOsdItem* item)
{
    if (item == _subMenuItem)
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
