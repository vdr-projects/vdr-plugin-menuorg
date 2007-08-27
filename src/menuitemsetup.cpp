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

#include "menuitemsetup.h"
#include <iostream>

cMenuItemSetup::cMenuItemSetup(void)
:cOsdMenu(tr("Item Setup"))
{
    itemTypeText[0] = "System";
    itemTypeText[1] = "Plugin";
    itemTypeText[2] = "Submenu";
    itemTypeText[3] = "Command";

    Add(new cMenuEditStraItem(tr("Item Type"),&_itemType, 4, itemTypeText));
    // TODO: add osd items for the selectet item type
}

eOSState cMenuItemSetup::ProcessKey(eKeys Key)
{
    dsyslog("menuorg: cMenuSetupItemSetup::ProcessKey called");
    std::cerr << "menuorg: cMenuSetupItemSetup::ProcessKey called" << std::endl;
    eOSState state = cOsdMenu::ProcessKey(Key);
    return state;
}
