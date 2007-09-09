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

#ifndef ___PLUGINMENUNODE_H
#define ___PLUGINMENUNODE_H

#include <string>
#include "MenuNode.h"

class cPlugin;
class IMenuNodeProcessor;

class PluginMenuNode: public MenuNode
{
    private:
        cPlugin* _plugin;
        int _pluginIndex;
        std::string _customTitle;
        std::string _pluginName;

    public:
        PluginMenuNode(std::string pluginName, std::string customTitle = "");
        std::string CustomTitle();
        std::string PluginName();
        int PluginIndex();
        std::string DisplayText();

        // MenuNode
        void Process(IMenuNodeProcessor* menuNodeProcessor);
        bool IsHidden();
        PluginMenuNode* Clone();

    private:
        bool HasMainMenuEntry();
        bool FindPluginByName(std::string name, cPlugin*& plugin, int& pluginIndex);
};

#endif
