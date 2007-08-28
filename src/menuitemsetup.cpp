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

#include <iostream>
#include "menuitemsetup.h"
#include "osdxmlitem.h"

cMenuItemSetup::cMenuItemSetup(cOsdXmlItem* osdXmlItem)
:cOsdMenu(tr("Item Setup"))
{
    itemTypeText[0] = "System";
    itemTypeText[1] = "Plugin";
    itemTypeText[2] = "Submenu";
    itemTypeText[3] = "Command";

    Add(new cMenuEditStraItem(tr("Item Type"),&_itemType, 4, itemTypeText));

    switch(_itemType)
    {
        case 0:
            // Add listItem of valid System Items
            //Add(new cMenuEditStraItem(tr("available System Items"),))
            // Add textItem for title attribute
            //Add(new cMenuEditStrItem(tr("title"), VAR, 64, NULL))
            break;

        case 1:
            // Add listItem of unused plugins or a submenu with the items
            //Add(new cMenuEditStraItem(tr("available Plugins Items"),))
            // Add textItem for title attribute
            //Add(new cMenuEditStrItem(tr("title"), VAR, 64, NULL))
            break;

        case 2:
            // Add textItem for name attribute
            //Add(new cMenuEditStrItem(tr("name"), VAR, 64, NULL))
            break;

        case 3:
            // Add textItem for name attribute
            //Add(new cMenuEditStrItem(tr("name"), VAR, 64, NULL))
            // Add textItem for command attribute
            //Add(new cMenuEditStrItem(tr("command"), VAR, 64, NULL))
            // Add boolItem for confirm attribute
            //Add(new cMenuEditBoolItem(tr("confirm"), &_confirm));
            break;
    }
}

// TODO: When exit check if the type was menu and now is changed -> bring a warning on the osd that the subitems will be deleted

eOSState cMenuItemSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);
    return state;
}
