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

const char* PluginSetup::SetupName::CustomMenuActive = "customMenuActive";
const char* PluginSetup::SetupName::UnconfiguredPluginsIncluded = "unconfiguredPluginsIncluded";
const char* PluginSetup::SetupName::HideMainMenuEntry = "hideMainMenuEntry";
const char* PluginSetup::SetupName::MenuSetupStyle = "menuSetupStyle";

PluginSetup::PluginSetup(bool& customMenuActive, bool& unconfiguredPluginsIncluded, bool& hideMainMenuEntry, bool& menuSetupStyle, MenuConfiguration& menuConfiguration)
    :_customMenuActive(customMenuActive), _unconfiguredPluginsIncluded(unconfiguredPluginsIncluded), _hideMainMenuEntry(hideMainMenuEntry), _menuSetupStyle(menuSetupStyle),
    _menuConfiguration(menuConfiguration)
{
    _newCustomMenuActive = _customMenuActive;
    _newUnconfiguredPluginsIncluded = _unconfiguredPluginsIncluded;
    _newHideMainMenuEntry = _hideMainMenuEntry;
    _newMenuSetupStyle = _menuSetupStyle;
    CreateMenuItems();
}

void PluginSetup::Store(void)
{
    SetupStore(SetupName::CustomMenuActive, _customMenuActive = _newCustomMenuActive);
    SetupStore(SetupName::UnconfiguredPluginsIncluded, _unconfiguredPluginsIncluded = _newUnconfiguredPluginsIncluded);
    SetupStore(SetupName::HideMainMenuEntry, _hideMainMenuEntry = _newHideMainMenuEntry);
    SetupStore(SetupName::MenuSetupStyle, _menuSetupStyle = _newMenuSetupStyle);
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
            return AddSubMenu(new cMenuOrgSetup(_menuConfiguration, _menuSetupStyle));
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
