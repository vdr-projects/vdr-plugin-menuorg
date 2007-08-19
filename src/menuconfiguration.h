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

#ifndef ___MENUCONFIGURARION_H
#define ___MENUCONFIGURATION_H

#include <string>
#include <vdr/osdbase.h>
#include "menunode.h"

namespace xmlpp { class Element; }

class MenuConfiguration
{
    private:
        static const std::string _dtd;

    public:
        MenuNode* LoadMenu(std::string menuFileName);

    private:
        void ParseElement(const xmlpp::Element* a_node, MenuNode* menuNode);
        eOSState MenuTextToVdrState(std::string menuText);
        bool FindPluginByName(std::string name, const char** mainMenuEntry, int& pluginIndex);
        MenuNode* AddSubMenuItem(std::string name, MenuNode* menu);
        void AddSystemMenuItem(std::string name, MenuNode* menu);
        void AddPluginMenuItem(std::string pluginName, MenuNode* menu);
};

#endif 
