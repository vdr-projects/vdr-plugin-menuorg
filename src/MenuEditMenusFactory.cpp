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
 * $Id: childlock.cpp 5951 2007-08-24 05:45:20Z svntcreutz $
 *
 */

#include "MenuEditMenusFactory.h"
#include "CommandMenuNode.h"
#include "PluginMenuNode.h"
#include "SystemMenuNode.h"
#include "SubMenuNode.h"
#include "SeparatorMenuNode.h"
#include <vdr/osdbase.h>
#include "RecursiveMenuSetup.h"

cOsdMenu* MenuEditMenusFactory::Create(MenuNode& menuNode, bool openSubmenuInsteadOfEditing)
{
    cOsdMenu* menu = NULL;
    MenuEditMenusFactory editMenusFactory(menu, openSubmenuInsteadOfEditing);
    menuNode.Process(&editMenusFactory);
    return menu;
}

void MenuEditMenusFactory::ProcessSystemMenuNode(SystemMenuNode* node)
{
    _menu = new cOsdMenu("Edit System Menu Node");
}

void MenuEditMenusFactory::ProcessPluginMenuNode(PluginMenuNode* node)
{
    _menu = new cOsdMenu("Edit Plugin Menu Node");
}

void MenuEditMenusFactory::ProcessSubMenuNode(SubMenuNode* node)
{
    if (_openSubmenuInsteadOfEditing)
    {
        _menu = new RecursiveMenuSetup(NULL, node);
    }
    else
    {
        _menu = new cOsdMenu("Edit Sub Menu Node");
    }
}

void MenuEditMenusFactory::ProcessCommandMenuNode(CommandMenuNode* node)
{
    _menu = new cOsdMenu("Edit Command Menu Node");
}

void MenuEditMenusFactory::ProcessSeparatorMenuNode(SeparatorMenuNode* nod)
{
    _menu = new cOsdMenu("Edit Separator Menu Node");
}

MenuEditMenusFactory::MenuEditMenusFactory(cOsdMenu*& menu, bool openSubmenuInsteadOfEditing)
    :_menu(menu)
{
    _openSubmenuInsteadOfEditing = openSubmenuInsteadOfEditing;
}
