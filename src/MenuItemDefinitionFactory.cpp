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

#include "MenuItemDefinitionFactory.h"
#include "SubMenuNode.h"
#include "SystemMenuNode.h"
#include "PluginMenuNode.h"
#include "CommandMenuNode.h"
#include "SeparatorMenuNode.h"
#include "OsdItemDefinition.h"
#include "PluginItemDefinition.h"
#include "SeparatorItemDefinition.h"
#include "OsdLineItem.h"
#include <string>

using namespace std;

MenuItemDefinition* MenuItemDefinitionFactory::CreateFromMenuNode(MenuNode* menuNode, bool isSelected)
{
    MenuItemDefinitionFactory* factory = new MenuItemDefinitionFactory(isSelected);
    menuNode->Process(factory);
    return factory->_createdMenuItemDefinition;
}

MenuItemDefinitionFactory::MenuItemDefinitionFactory(bool isSelected)
{
    _isSelected = isSelected;
}

void MenuItemDefinitionFactory::ProcessSystemMenuNode(SystemMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(node, new cOsdItem(node->DisplayText().c_str(), node->State().OSState()), false);
}

void MenuItemDefinitionFactory::ProcessPluginMenuNode(PluginMenuNode* node)
{
    _createdMenuItemDefinition = new PluginItemDefinition(node, node->DisplayText(), node->PluginIndex());   
}

void MenuItemDefinitionFactory::ProcessSubMenuNode(SubMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(node, new cOsdItem(node->Text().c_str(), osUser1), _isSelected);
}

void MenuItemDefinitionFactory::ProcessCommandMenuNode(CommandMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(node, new cOsdItem(node->Text().c_str(), osUser2), _isSelected);
}

void MenuItemDefinitionFactory::ProcessSeparatorMenuNode(SeparatorMenuNode* node)
{
    _createdMenuItemDefinition = new SeparatorItemDefinition(node, new cOsdSeparatorItem(node->DisplayText().c_str()));
}
