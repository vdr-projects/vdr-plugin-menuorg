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

#ifndef MENUITEMDEFINITIONFACTORY_H_
#define MENUITEMDEFINITIONFACTORY_H_

#include "IMenuNodeProcessor.h"

class MenuNode;
class SystemMenuNode;
class PluginMenuNode;
class SubMenuNode;
class CommandMenuNode;
class SeparatorMenuNode;
class MenuItemDefinition;

class MenuItemDefinitionFactory: IMenuNodeProcessor
{
    private:
        MenuItemDefinition* _createdMenuItemDefinition;
        bool _isSelected;

    public:
        static MenuItemDefinition* CreateFromMenuNode(MenuNode* menuNode, bool isSelected);

        // IMenuNodeProcessor
        void ProcessSystemMenuNode(SystemMenuNode* node);
        void ProcessPluginMenuNode(PluginMenuNode* node);
        void ProcessSubMenuNode(SubMenuNode* node);
        void ProcessCommandMenuNode(CommandMenuNode* node);
        void ProcessSeparatorMenuNode(SeparatorMenuNode* node);

    private:
        MenuItemDefinitionFactory(bool isSelected);
};

#endif
