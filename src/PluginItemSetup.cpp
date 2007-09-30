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

#include <vdr/plugin.h>
#include "PluginItemSetup.h"

cPluginItemSetup::cPluginItemSetup(PluginMenuNode* node)
:cOsdMenu(tr("Edit Plugin Menu Item"), 10)
{
    _newPluginIndex = node->PluginIndex();
    strn0cpy(_newTitle, node->CustomTitle().c_str(), sizeof(_newTitle));
    getPlugins();
    CreateMenuItems();
}

cPluginItemSetup::~cPluginItemSetup()
{
    // TODO: write back the changes
    //delete[] pluginList;
}

void cPluginItemSetup::CreateMenuItems()
{
    // Add listItem of unused plugins or a submenu with the items
    //Add(new cMenuEditStraItem(tr("available Plugins Items"), &_newPluginIndex, pluginList.size(), pluginList));
    //Add(new cMenuEditStraItem(tr("available Plugins Items"), &_newPluginIndex, 0, pluginList));
    // Add textItem for title attribute
    Add(new cMenuEditStrItem(tr("title"), _newTitle, sizeof(_newTitle), NULL));
}

void cPluginItemSetup::getPlugins()
{
    int i=0;
    while (cPlugin *currentPlugin = cPluginManager::GetPlugin(i))
    {
        //pluginList.push_back(currentPlugin->Name());
        //pluginList[i] = new char* ( (char) currentPlugin->Name());
        i++;
    }
}

eOSState cPluginItemSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);
    return state;
}
