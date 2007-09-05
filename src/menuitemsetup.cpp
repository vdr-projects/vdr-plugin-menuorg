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

    _osdXmlItem = osdXmlItem;
    _newItemType = _osdXmlItem->getItemType();
    //_newName = _osdXmlItem->getNameAttribute().c_str();
    //_newTitle = _osdXmlItem->getTitleAttribute().c_str();
    asprintf(&_newTitle, "%s", _osdXmlItem->getTitleAttribute().c_str());
    //_newCommand = _osdXmlItem->getCommandAttribute().c_str();
    CreateMenuItems();
}

cMenuItemSetup::~cMenuItemSetup()
{
    _osdXmlItem->setNameAttribute(_newName);
    _osdXmlItem->setTitleAttribute(_newTitle);
    _osdXmlItem->setCommandAttribute(_newCommand);
    free(_newName);
    free(_newTitle);
    free(_newCommand);
}

// TODO: When exit check if the type was menu and now is changed -> bring a warning on the osd that the subitems will be deleted

void cMenuItemSetup::CreateMenuItems(void)
{
    esyslog("menuorg: _newItemType=%d", _newItemType);
    esyslog("menuorg: _newTitle=%s", _newTitle);

    Clear();

    Add(new cMenuEditStraItem(tr("Item Type"), (int*) &_newItemType, 4, itemTypeText));

    switch(_newItemType)
    {
        case 0:
            // Add listItem of valid System Items
            //Add(new cMenuEditStraItem(tr("available System Items"),))
            // Add textItem for title attribute
            Add(new cMenuEditStrItem(tr("title"), _newTitle, 64, NULL));
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

eOSState cMenuItemSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);
    return state;
}
