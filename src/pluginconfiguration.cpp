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
 * $Id: pluginsetup.h 6098 2007-08-28 12:20:45Z svntcreutz $
 *
 */

#include "pluginconfiguration.h"
#include <stdlib.h>
#include <strings.h>

const char* PluginConfiguration::SetupName::CustomMenuActive = "customMenuActive";
const char* PluginConfiguration::SetupName::UnconfiguredPluginsIncluded = "unconfiguredPluginsIncluded";
const char* PluginConfiguration::SetupName::HideMainMenuEntry = "hideMainMenuEntry";
const char* PluginConfiguration::SetupName::MenuSetupStyle = "menuSetupStyle";

PluginConfiguration::PluginConfiguration()
{
    SetDefaults();
}

bool PluginConfiguration::CustomMenuActive()
{
	return _customMenuActive;
}

bool PluginConfiguration::UnconfiguredPluginsInluded()
{
    return _unconfiguredPluginsIncluded;
}

bool PluginConfiguration::MainMenuEntryHidden()
{
    return _hideMainMenuEntry;
}

int PluginConfiguration::MenuSetupStyle()
{
    return _menuSetupStyle;
}

void PluginConfiguration::SetDefaults()
{
    _customMenuActive = true;
    _hideMainMenuEntry = true;
    _menuSetupStyle = 0;
    _unconfiguredPluginsIncluded = true;
}

bool PluginConfiguration::SetConfigurationOptionByName(const char* Name, const char* Value)
{
   if (!strcasecmp(Name, SetupName::CustomMenuActive))
    {
        _customMenuActive = (atoi(Value) != 0);
    }
    else if(!strcasecmp(Name, SetupName::UnconfiguredPluginsIncluded))
    {
        _unconfiguredPluginsIncluded = (atoi(Value) != 0);
    }
    else if(!strcasecmp(Name, SetupName::HideMainMenuEntry))
    {
        _hideMainMenuEntry = (atoi(Value) != 0);
    }
    else if(!strcasecmp(Name, SetupName::MenuSetupStyle))
    {
        _menuSetupStyle = (atoi(Value) != 0);
    }
    else
        return false;

    return true;
}
