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
#include <vdr/menu.h>
#include "menuorg.h"
#include "pluginsetup.h"
#include "menusetup.h"

PluginSetup::PluginSetup(PluginConfiguration& pluginConfiguration, MenuConfiguration& menuConfiguration)
    :_pluginConfiguration(pluginConfiguration), _menuConfiguration(menuConfiguration)
{
    CreateMenuItems();
}

void PluginSetup::Store(void)
{
    SetupStore(PluginConfiguration::SetupName::CustomMenuActive, _pluginConfiguration._customMenuActive = _newCustomMenuActive);
    SetupStore(PluginConfiguration::SetupName::UnconfiguredPluginsIncluded, _pluginConfiguration._unconfiguredPluginsIncluded = _newUnconfiguredPluginsIncluded);
    SetupStore(PluginConfiguration::SetupName::HideMainMenuEntry, _pluginConfiguration._hideMainMenuEntry = _newHideMainMenuEntry);
    SetupStore(PluginConfiguration::SetupName::MenuSetupStyle, _pluginConfiguration._menuSetupStyle = _newMenuSetupStyle);
}

eOSState PluginSetup::ProcessKey(eKeys Key)
{
    eOSState state = cOsdMenu::ProcessKey(Key);

    if (HasSubMenu())
    {
        return state;
    }
    switch(state)
    {
        case osUser1:
            return AddSubMenu(new cMenuOrgSetup(_menuConfiguration, _pluginConfiguration._menuSetupStyle));
            break;

        case osContinue:
            if(NORMALKEY(Key)==kUp || NORMALKEY(Key)==kDown)
            {
                cOsdItem *item=Get(Current());
                if(item) item->ProcessKey(kNone);
            }
            break;

        case osUnknown:
            if(Key==kOk)
            {
                Store();
                state=osBack;
            }
            break;

        default:
            break;
    }
    return state;
}

void PluginSetup::CreateMenuItems()
{
    Add(new cMenuEditBoolItem(tr("Enable custom menu"), &_newCustomMenuActive));
    Add(new cMenuEditBoolItem(tr("Include unconfigured Plugins"), &_newUnconfiguredPluginsIncluded));
    Add(new cMenuEditBoolItem(tr("Hide MainMenu Entry"), &_newHideMainMenuEntry));
    Add(new cMenuEditBoolItem(tr("Menusetup Style"), &_newMenuSetupStyle, tr("MenuBased"),tr("Flat")));
    Add(new cOsdItem(tr("Configure Menu"), osUser1));
}
