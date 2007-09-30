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

#include <vdr/osdbase.h>
#include "MenuEditMenusFactory.h"
#include "RecursiveMenuSetup.h"

#include "CommandMenuNode.h"
#include "PluginMenuNode.h"
#include "SeparatorMenuNode.h"
#include "SubMenuNode.h"
#include "SystemMenuNode.h"

#include "CommandItemSetup.h"
#include "PluginItemSetup.h"
#include "SeparatorItemSetup.h"
#include "SubMenuItemSetup.h"
#include "SystemItemSetup.h"

cOsdMenu* MenuEditMenusFactory::Create(MenuNode& menuNode, bool openSubmenuInsteadOfEditing)
{
    cOsdMenu* menu = NULL;
    MenuEditMenusFactory editMenusFactory(menu, openSubmenuInsteadOfEditing);
    menuNode.Process(&editMenusFactory);
    return menu;
}

void MenuEditMenusFactory::ProcessSystemMenuNode(SystemMenuNode* node)
{
    _menu = new cSystemItemSetup(node);
}

void MenuEditMenusFactory::ProcessPluginMenuNode(PluginMenuNode* node)
{
    _menu = new cPluginItemSetup(node);
}

void MenuEditMenusFactory::ProcessSubMenuNode(SubMenuNode* node)
{
    if (_openSubmenuInsteadOfEditing)
    {
        _menu = new RecursiveMenuSetup(NULL, node);
    }
    else
    {
        _menu = new cSubMenuItemSetup(node);
    }
}

void MenuEditMenusFactory::ProcessCommandMenuNode(CommandMenuNode* node)
{
    _menu = new cCommandItemSetup(node);
}

void MenuEditMenusFactory::ProcessSeparatorMenuNode(SeparatorMenuNode* node)
{
    _menu = new cSeparatorItemSetup(node);
}

MenuEditMenusFactory::MenuEditMenusFactory(cOsdMenu*& menu, bool openSubmenuInsteadOfEditing)
    :_menu(menu)
{
    _openSubmenuInsteadOfEditing = openSubmenuInsteadOfEditing;
}
