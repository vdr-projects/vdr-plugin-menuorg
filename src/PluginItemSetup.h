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

#ifndef ___PLUGINITEMSETUP_H
#define ___PLUGINITEMSETUP_H

#include <vector>
#include <vdr/menu.h>
#include "PluginMenuNode.h"

class cPluginItemSetup : public cOsdMenu
{
    private:
        //std::vector<const char*> pluginList;
        char **pluginList;
        int _newPluginIndex;
        char _newTitle[256];

    public:
        cPluginItemSetup(PluginMenuNode* node);
        ~cPluginItemSetup(void);
        virtual eOSState ProcessKey(eKeys Key);

    private:
        void CreateMenuItems(void);
        void getPlugins(void);
};

#endif
