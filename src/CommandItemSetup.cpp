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

#include "CommandItemSetup.h"

cCommandItemSetup::cCommandItemSetup(CommandMenuNode* node)
:cOsdMenu(tr("Edit Command Menu Item"))
{
    _newName = node->Text();
    _newCommand = node->Command();
    _newConfirm = node->ShouldConfirm();
    CreateMenuItems();
}

cCommandItemSetup::~cCommandItemSetup()
{
    // TODO: write back the changes
    free(_newName);
    free(_newCommand);
    free(_newConfirm);
}

void cCommandItemSetup::CreateMenuItems()
{
    // Add textItem for name attribute
    Add(new cMenuEditStrItem(tr("name"), _newName, 64, NULL));

    // Add textItem for command attribute
    Add(new cMenuEditStrItem(tr("command"), _newCommand, 200, NULL));

    // Add boolItem for confirm attribute
    Add(new cMenuEditBoolItem(tr("confirm"), _newConfirm));
}

eOSState cCommandItemSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);
    return state;
}
