#include "submenuprovider.h"
#include "submenuitem.h"
#include "vdrmenuitem.h"
#include "pluginmenuitem.h"
#include <vdr/plugin.h>

SubMenuProvider::SubMenuProvider()
{
    //CreateTestMenus();
    _oXmlMenu.LoadXmlMenu();
    _currentMenu = _oXmlMenu.GetMenuTree();
}
/*
void SubMenuProvider::CreateTestMenus()
{
    MenuNode* subMenu1 =_rootMenuNode.AddChild(new SubMenuItem("Custom menu 1"));
        subMenu1->AddChild(new VdrMenuItem(tr("Schedule"), osSchedule));
        subMenu1->AddChild(new VdrMenuItem(tr("Channels"), osChannels));
        MenuNode* subMenu1_1 = subMenu1->AddChild(new SubMenuItem("Custom menu 1.1"));
            subMenu1_1->AddChild(new VdrMenuItem(tr("Timers"), osTimers));
            subMenu1_1->AddChild(new VdrMenuItem(tr("Recordings"), osRecordings));
    MenuNode* subMenu2 =_rootMenuNode.AddChild(new SubMenuItem("Custom menu 2"));
        //plugins
        int i=0;
        while (cPlugin *p = cPluginManager::GetPlugin(i))
        {
            if (const char *item = p->MainMenuEntry())
            {
                  subMenu2->AddChild(new PluginMenuItem(item, i));
            }
            i++;
        }
    _rootMenuNode.AddChild(new VdrMenuItem(tr("Setup"), osSetup));
    if (Commands.Count())
        _rootMenuNode.AddChild(new VdrMenuItem(tr("Commands"), osCommands));
}
*/
MainMenuItemsList* SubMenuProvider::MainMenuItems()
{
    ResetMainMenuItemsList();

    for (MenuNodeList::iterator i = _currentMenu->Childs().begin();
      i != _currentMenu->Childs().end(); i++)
    {
        _currentMainMenuItems.push_back((*i)->CreateMainMenuItem());
    }

    return &_currentMainMenuItems;
}

void SubMenuProvider::ResetMainMenuItemsList()
{

    for( MainMenuItemsList::iterator i = _currentMainMenuItems.begin();
      i != _currentMainMenuItems.end(); i++)
    {
       delete *i;
    }
    _currentMainMenuItems.clear(); 
}

void SubMenuProvider::EnterSubMenu(cOsdItem* item)
{
    for(unsigned int itemIndex=0; itemIndex < _currentMainMenuItems.size(); itemIndex++)
    {
        MainMenuItem* menuItem = _currentMainMenuItems.at(itemIndex);
        if (menuItem->IsCustomMenuItem() && (menuItem->CustomMenuItem() == item))
        {
            _currentMenu = _currentMenu->Childs().at(itemIndex);
            break;
        }
    }
}

bool SubMenuProvider::LeaveSubMenu()
{
    if (_currentMenu->Parent())
    {
        _currentMenu = _currentMenu->Parent();
        return true;
    }
    else
    {
        return false;
    }
}