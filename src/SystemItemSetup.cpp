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

#include "SystemItemSetup.h"
#include "VdrState.h"

SystemItemSetup::SystemItemSetup(SystemMenuNode* node)
:cOsdMenu(tr("Edit System Menu Item"), 10)
{
    strn0cpy(_newName, node->State().Name().c_str(), sizeof(_newName));
    strn0cpy(_newTitle, node->CustomTitle().c_str(), sizeof(_newTitle));
    _node = node;
    CreateMenuItems();
}

SystemItemSetup::~SystemItemSetup()
{
    // TODO: write back the changes
}

void SystemItemSetup::CreateMenuItems()
{
    // Add listItem of valid System Items
    //Add(new cMenuEditStraItem(tr("available System Items"),))

    // Add textItem for title attribute
    Add(new cMenuEditStrItem(tr("title"), _newTitle, sizeof(_newTitle), NULL));
}

void SystemItemSetup::Store()
{
    _node->State(VdrState::ByName(_newName));
    _node->CustomTitle(_newTitle);
}

eOSState SystemItemSetup::ProcessKey(eKeys Key)
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
