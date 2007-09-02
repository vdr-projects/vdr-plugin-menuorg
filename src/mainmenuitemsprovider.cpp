/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (C) 2007 Thomas Creutz, Tobias Grimm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id$
 *
 */

#include "mainmenuitemsprovider.h"
#include "submenunode.h"
#include "systemmenunode.h"
#include "pluginmenunode.h"
#include "commandmenunode.h"
#include <vdr/plugin.h>
#include "childlock.h"
#include "menuconfiguration.h"
#include "osditemdefinition.h"
#include "pluginitemdefinition.h"

MainMenuItemsProvider::MainMenuItemsProvider(MenuConfiguration& menuConfiguration)
    :_menuConfiguration(menuConfiguration)
{
    EnterRootMenu();
}

MainMenuItemsProvider::~MainMenuItemsProvider()
{
    delete _rootMenu;
    ResetMainMenuItemsList();
}

MenuItemDefinitions* MainMenuItemsProvider::MainMenuItems()
{
    ResetMainMenuItemsList();

    for (MenuNodeList::iterator i = _currentMenu->Childs().begin();
      i != _currentMenu->Childs().end(); i++)
    {
        if (!(*i)->IsHidden())
        {
            (*i)->Process(this);
            _currentMainMenuItems.push_back(_createdMenuItemDefinition);
        }
    }

    return &_currentMainMenuItems;
}

void MainMenuItemsProvider::ResetMainMenuItemsList()
{

    for( MenuItemDefinitions::iterator i = _currentMainMenuItems.begin();
      i != _currentMainMenuItems.end(); i++)
    {
       delete *i;
    }
    _currentMainMenuItems.clear(); 
}

void MainMenuItemsProvider::EnterRootMenu()
{
    _currentMenu = _rootMenu = _menuConfiguration.MenuTree();;
}

void MainMenuItemsProvider::EnterSubMenu(cOsdItem* item)
{
    int itemIndex = IndexOfCustomOsdItem(item);
    if (itemIndex >= 0)
    {
        _currentMenu = _currentMenu->Childs().at(itemIndex);
    }
}

bool MainMenuItemsProvider::LeaveSubMenu()
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

cOsdMenu* MainMenuItemsProvider::Execute(cOsdItem* item)
{
    int itemIndex = IndexOfCustomOsdItem(item);
    if (itemIndex >= 0)
    {
        return _currentMenu->Childs().at(itemIndex)->Execute();
    }
    return NULL;
}

int MainMenuItemsProvider::IndexOfCustomOsdItem(cOsdItem* item)
{
    for(unsigned int itemIndex=0; itemIndex < _currentMainMenuItems.size(); itemIndex++)
    {
        IMenuItemDefinition* menuItem = _currentMainMenuItems.at(itemIndex);
        if (menuItem->IsCustomOsdItem() && (menuItem->CustomOsdItem() == item))
        {
            return itemIndex;
        }
    }
    return -1;
}

void MainMenuItemsProvider::ProcessCommandMenuNode(CommandMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdItem(node->Text().c_str(), osUser2));
}

void MainMenuItemsProvider::ProcessPluginMenuNode(PluginMenuNode* node)
{
    _createdMenuItemDefinition = new PluginItemDefinition(node->Title().c_str(), node->PluginIndex());   
}

void MainMenuItemsProvider::ProcessSubMenuNode(SubMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdItem(node->Text().c_str(), osUser1));
}

void MainMenuItemsProvider::ProcessSystemMenuNode(SystemMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdItem(tr(node->Text().c_str()), node->State()));
    
}
