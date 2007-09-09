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

#ifndef ___RECURSIVEMENUSETUP_H_
#define ___RECURSIVEMENUSETUP_H_

#include <vdr/menu.h>
#include "IMenuNodeProcessor.h"

class MenuConfigurationRepository;
class MenuNode;

class RecursiveMenuSetup: public cOsdMenu
{
    private:
        MenuConfigurationRepository* _menuConfigurationRepository;
        SubMenuNode* _menuConfiguration;
        SubMenuNode* _currentRootMenuNode;
        bool _moving;

    public:
        RecursiveMenuSetup(MenuConfigurationRepository* menuConfigurationRepository, SubMenuNode* rootMenuNode = NULL);
        ~RecursiveMenuSetup();

           // cOsdMenu
           eOSState ProcessKey(eKeys Key);

    private:
        void CreateMenuItems();
        void ShowHelp();
        void StartMoving();
        void StopMoving();
        eOSState MoveCurrentItem(bool moveUp);
        eOSState ShowEditMenuForSelectedItem(bool openSubmenuInsteadOfEditing);
        MenuNode* SelectedItem();
};

#endif