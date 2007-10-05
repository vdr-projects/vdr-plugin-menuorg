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

#include "SubMenuItemSetup.h"

const char AllowedChars[] = "$ abcdefghijklmnopqrstuvwxyz0123456789-.#~\\^$[]|()*+?{}/:%";

SubMenuItemSetup::SubMenuItemSetup(SubMenuNode* node)
:cOsdMenu(tr("Edit Sub Menu Item"), 10)
{
    strn0cpy(_newName, node->Text().c_str(), sizeof(_newName));
    CreateMenuItems();
}

SubMenuItemSetup::~SubMenuItemSetup()
{
    // TODO: write back the changes
}

void SubMenuItemSetup::CreateMenuItems()
{
    // Add textItem for name attribute
    Add(new cMenuEditStrItem(tr("name"), _newName, sizeof(_newName), tr(AllowedChars)));
}

void SubMenuItemSetup::Store()
{
    _node->Text(_newName);
}

eOSState SubMenuItemSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);

    if(state == osUnknown)
    {
        if(Key == kOk)
        {
            Store();
            state = osBack;
        }
    }
    return state;
}
