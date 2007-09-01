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

#ifndef ___PLUGINCONFIGURATION_H_
#define ___PLUGINCONFIGURATION_H_

class PluginConfiguration
{
    friend class PluginSetup;
    
    private:
        struct SetupName
        {
            static const char* CustomMenuActive;
            static const char* UnconfiguredPluginsIncluded;
            static const char* HideMainMenuEntry;
            static const char* MenuSetupStyle;
        };

	private:
        bool _customMenuActive;
        bool _unconfiguredPluginsIncluded; 
        bool _hideMainMenuEntry;
        int _menuSetupStyle;

	public:
        PluginConfiguration();
        bool SetConfigurationOptionByName(const char* Name, const char* Value);
        bool CustomMenuActive();
        bool UnconfiguredPluginsInluded();
        bool MainMenuEntryHidden();
        int MenuSetupStyle();

	private:
        void SetDefaults();
};

#endif

