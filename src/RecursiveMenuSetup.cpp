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

#include "RecursiveMenuSetup.h"
#include "SubMenuNode.h"
#include "MenuConfigurationRepository.h"
#include "MenuSetupItemsFactory.h"
#include "MenuEditMenusFactory.h"

RecursiveMenuSetup::RecursiveMenuSetup(MenuConfigurationRepository* menuConfigurationRepository, SubMenuNode* rootMenuNode)
    :cOsdMenu(tr("Menu Configuration")), _menuConfigurationRepository(menuConfigurationRepository)
{
    _moving = false;
    if (rootMenuNode)
    {
        _currentRootMenuNode = rootMenuNode;
        _menuConfiguration = NULL;
    }
    else
    {
        _currentRootMenuNode = _menuConfiguration = menuConfigurationRepository->Load()->Clone();
    }
    CreateMenuItems();
    ShowHelp();
}

RecursiveMenuSetup::~RecursiveMenuSetup()
{
    delete _menuConfiguration;
}

void RecursiveMenuSetup::CreateMenuItems()
{
    MenuSetupItemsFactory menuItemSetupFactory(this);
    menuItemSetupFactory.SetupItems(*_currentRootMenuNode);
}

eOSState RecursiveMenuSetup::ProcessKey(eKeys Key)
{
    // Catch keys that should not be processed by the base class
    if (_moving)
    {
        if ((Key == kUp) || (Key == kDown))
        {
            return MoveCurrentItem(Key == kUp);
        }
        if ((Key == kLeft) || (Key == kRight))
        {
            return osContinue;
        }
    }

    // Process keys in base class
    eOSState state = cOsdMenu::ProcessKey(Key);
    if(HasSubMenu())
    {

        return state;
    }

    if ((state == osBack) || (state == osEnd))
    {
        if (!_currentRootMenuNode->Parent())   
        {
            _menuConfigurationRepository->Save(*_currentRootMenuNode);
        }
    }

    // Process unprocessed keys
    if ((state == osUnknown) && SelectedItem())
    {
        if (_moving)
        {
            switch(Key)
            {
                case kOk:
                    StopMoving();
                    return osContinue;
                default: 
                    break;
            }
        }
        else
        {
            switch(Key)
            {
                case kOk:
                    return ShowEditMenuForSelectedItem(true);
                case kRed:
                    StartMoving();
                    break;
                case kBlue:
                    return ShowEditMenuForSelectedItem(false);
                default: 
                    break;
            }
        }
    }

    return state;
}

void RecursiveMenuSetup::StartMoving()
{
    _moving = true;
    SetStatus("Move with Up/Down and confirm with OK");
    SetHelp(NULL);
}

void RecursiveMenuSetup::StopMoving()
{
    _moving = false;
    SetStatus(NULL);
    ShowHelp();
}

eOSState RecursiveMenuSetup::MoveCurrentItem(bool moveUp)
{
    int oldPos = Current();
    int newPos = Current();

    MenuNode* node = _currentRootMenuNode->Childs()->at(oldPos);

    if ((oldPos > 0) && moveUp)
    {
        newPos = oldPos - 1;
    }
    else if ((oldPos < Count() - 1) && !moveUp)
    {
        newPos = oldPos + 1;
    }

    if (oldPos != newPos)
    {
        _currentRootMenuNode->Childs()->erase(_currentRootMenuNode->Childs()->begin() + oldPos);
        _currentRootMenuNode->Childs()->insert(_currentRootMenuNode->Childs()->begin() + newPos, node);

        Clear();
        CreateMenuItems();
        SetCurrent(Get(newPos));
        Display();
    }

    return osContinue;
}

void RecursiveMenuSetup::ShowHelp()
{
    SetHelp("Move", "Delete", "New", "Edit");
}

eOSState RecursiveMenuSetup::ShowEditMenuForSelectedItem(bool openSubmenuInsteadOfEditing)
{
    cOsdMenu* editMenu = MenuEditMenusFactory::Create(*SelectedItem(), openSubmenuInsteadOfEditing);
    if (editMenu)
    {
        return AddSubMenu(editMenu);
    }
    else
    {
        return osContinue;
    }
}

MenuNode* RecursiveMenuSetup::SelectedItem()
{
    return _currentRootMenuNode->Childs()->at(Current());
}
