#include "submenuprovider.h"
#include "submenuitem.h"
#include "vdrmenuitem.h"
#include "pluginmenuitem.h"
#include <vdr/plugin.h>

SubMenuProvider::SubMenuProvider(MenuNode* rootMenu)
{
     _currentMenu = _rootMenu = rootMenu;
}

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

void SubMenuProvider::EnterRootMenu()
{
    _currentMenu = _rootMenu;
}

void SubMenuProvider::EnterSubMenu(cOsdItem* item)
{
    for(unsigned int itemIndex=0; itemIndex < _currentMainMenuItems.size(); itemIndex++)
    {
        IMainMenuItem* menuItem = _currentMainMenuItems.at(itemIndex);
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
