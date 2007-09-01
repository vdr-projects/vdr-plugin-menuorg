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
#include <vector>
#include <vdr/osdbase.h>
#include <libxml++/libxml++.h>
#include <glibmm/ustring.h>

namespace xmlpp { class Element; }
class MenuNode;
class cPlugin;

class MenuConfiguration
{
    private:
        static const std::string _dtd;
        bool _unconfiguredPluginsShouldBeIncluded;
        std::vector<std::string> _configuredPlugins;
        xmlpp::Element* _configuration;
        xmlpp::DomParser _parser;

    public:
        MenuConfiguration(std::string menuFileName, bool unconfiguredPluginsShouldBeIncluded);
        MenuNode* MenuTree();
        xmlpp::Element* Configuration();

    private:
        void CreateMenuTree(const xmlpp::Element* menuRoot, MenuNode* menuNode);
        eOSState MenuTextToVdrState(std::string menuText);
        bool FindPluginByName(std::string name, cPlugin*& plugin, int& pluginIndex);
        MenuNode* AddSubMenuNode(std::string name, MenuNode* menu);
        void AddSystemMenuNode(std::string name, std::string title, MenuNode* menu);
        void AddPluginMenuNode(std::string pluginName, std::string title, MenuNode* menu);
        void AddUnconfiguredPlugins(MenuNode* menu);
        void AddCommandMenuNode(std::string name, std::string command, bool confirm, MenuNode* menu);
        std::string UnicodeToLocaleOrIso8859(Glib::ustring unicodeString);
};

#endif 
