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
 * $Id: mainmenuitemsprovider.cpp 6133 2007-09-05 00:00:12Z svntobi $
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
#include "OsdLineItem.h"
#include <string>

using namespace std;

IMenuItemDefinition* MenuItemDefinitionFactory::CreateFromMenuNode(MenuNode* menuNode)
{
    MenuItemDefinitionFactory* factory = new MenuItemDefinitionFactory();
    menuNode->Process(factory);
    return factory->_createdMenuItemDefinition;
}

void MenuItemDefinitionFactory::ProcessSystemMenuNode(SystemMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdItem(node->DisplayText().c_str(), node->State().OSState()));
}

void MenuItemDefinitionFactory::ProcessPluginMenuNode(PluginMenuNode* node)
{
    _createdMenuItemDefinition = new PluginItemDefinition(node->DisplayText(), node->PluginIndex());   
}

void MenuItemDefinitionFactory::ProcessSubMenuNode(SubMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdItem(node->Text().c_str(), osUser1));
}

void MenuItemDefinitionFactory::ProcessCommandMenuNode(CommandMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdItem(node->Text().c_str(), osUser2));
}

void MenuItemDefinitionFactory::ProcessSeparatorMenuNode(SeparatorMenuNode* node)
{
    _createdMenuItemDefinition = new OsdItemDefinition(new cOsdSeparatorItem(node->DisplayText().c_str()));
}
