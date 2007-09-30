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

#include "PluginItemSetup.h"

cPluginItemSetup::cPluginItemSetup(PluginMenuNode* node)
:cOsdMenu(tr("Edit Plugin Menu Item"))
{
    asprintf(&_newName, "%s", node->PluginName().c_str());
    asprintf(&_newTitle, "%s", node->CustomTitle().c_str());
//    _newName = node->PluginName();
//    _newTitle = node->CustomTitle();
    CreateMenuItems();
}

cPluginItemSetup::~cPluginItemSetup()
{
    // TODO: write back the changes
    free(_newName);
    free(_newTitle);
}

void cPluginItemSetup::CreateMenuItems()
{
    // Add listItem of unused plugins or a submenu with the items
    //Add(new cMenuEditStraItem(tr("available Plugins Items"),))
    // Add textItem for title attribute
    Add(new cMenuEditStrItem(tr("title"), _newTitle, 64, NULL));
}

eOSState cPluginItemSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);
    return state;
}
