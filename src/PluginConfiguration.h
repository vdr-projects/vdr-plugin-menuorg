/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (c) 2007 - 2008 Tobias Grimm <vdr@e-tobi.net>
 * Copyright (c) 2007        Thomas Creutz <thomas.creutz@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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
        };

    private:
        bool _customMenuActive;
        bool _unconfiguredPluginsIncluded; 

    public:
        PluginConfiguration();
        bool SetConfigurationOptionByName(const char* Name, const char* Value);
        bool CustomMenuActive();
        bool UnconfiguredPluginsInluded();

    private:
        void SetDefaults();
};

#endif

