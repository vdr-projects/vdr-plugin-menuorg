/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (c) 2007 - 2008 Tobias Grimm <vdr@e-tobi.net>
 * Copyright (c) 2007        Thomas Creutz <thomas.creutz@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * $Id$
 *
 */

#include "MainMenuItemsProvider.h"
#include "SubMenuNode.h"
#include "MenuConfigurationRepository.h"
#include "MenuItemDefinitionFactory.h"

MainMenuItemsProvider::MainMenuItemsProvider(MenuConfigurationRepository& menuConfigurationRepository)
    :_menuConfigurationRepository(menuConfigurationRepository)
{
    EnterRootMenu();
    _previousMenu = NULL;
}

MainMenuItemsProvider::~MainMenuItemsProvider()
{
    ResetMainMenuItemsList();
}

MenuItemDefinitions* MainMenuItemsProvider::MainMenuItems()
{
    ResetMainMenuItemsList();

    for (MenuNodeList::iterator i = _currentMenu->Childs()->begin();
      i != _currentMenu->Childs()->end(); i++)
    {
        if (!(*i)->IsHidden())
        {
            bool isSelected = ((*i) == _previousMenu);
            _currentMainMenuItems.push_back(MenuItemDefinitionFactory::CreateFromMenuNode(*i, isSelected));
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
    _currentMenu = _menuConfigurationRepository.Load();
    // TODO; Handling of unloadable config file should not be done here
}

void MainMenuItemsProvider::EnterSubMenu(cOsdItem* item)
{
    if (MenuNode* menuNode = MenuNodeMatchingOsdItem(item))
    {
        menuNode->Process(this);
    }
}

bool MainMenuItemsProvider::LeaveSubMenu()
{
    if (_currentMenu->Parent())
    {
        _previousMenu = _currentMenu;
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
    if (MenuNode* menuNode = MenuNodeMatchingOsdItem(item))
    {
        return menuNode->Execute();
    }
    return NULL;
}

MenuNode* MainMenuItemsProvider::MenuNodeMatchingOsdItem(cOsdItem* item)
{
    for(unsigned int itemIndex=0; itemIndex < _currentMainMenuItems.size(); itemIndex++)
    {
        IMenuItemDefinition* menuItem = _currentMainMenuItems.at(itemIndex);
        if (menuItem->IsCustomOsdItem() && (menuItem->CustomOsdItem() == item))
        {
            return _currentMenu->Childs()->at(itemIndex);
        }
    }
    return NULL;
}

void MainMenuItemsProvider::ProcessCommandMenuNode(CommandMenuNode* node)
{
}

void MainMenuItemsProvider::ProcessPluginMenuNode(PluginMenuNode* node)
{
}

void MainMenuItemsProvider::ProcessSubMenuNode(SubMenuNode* node)
{
    _currentMenu = node;
}

void MainMenuItemsProvider::ProcessSystemMenuNode(SystemMenuNode* node)
{
}

void MainMenuItemsProvider::ProcessSeparatorMenuNode(SeparatorMenuNode* node)
{
}
