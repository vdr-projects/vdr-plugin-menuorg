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

#include <vdr/menu.h>

class cMenuOrgPluginSetup : public cMenuSetupPage
{
    private:
        int _newpluginIsActive;
        int _newshowLostPlugins;
        int* _pluginIsActive;
        int* _showLostPlugins;

    protected:
        virtual void Store(void);

    public:
        cMenuOrgPluginSetup(int *pluginActive, int *getLostPlugins);
        virtual eOSState ProcessKey(eKeys Key);
};
