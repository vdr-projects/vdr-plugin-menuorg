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

#include "MenuSetupItemsFactory.h"
#include "SubMenuNode.h"
#include "SystemMenuNode.h"
#include "PluginMenuNode.h"
#include "CommandMenuNode.h"
#include "SeparatorMenuNode.h"
#include <string>
#include <vdr/osdbase.h>

using namespace std;

MenuSetupItemsFactory::MenuSetupItemsFactory(cOsdMenu* osdMenu)
{
    _osdMenu = osdMenu;
}

void MenuSetupItemsFactory::SetupItems(SubMenuNode& rootMenu)
{
    for (MenuNodeList::iterator i = rootMenu.Childs()->begin(); i != rootMenu.Childs()->end(); i++)
    {
        (*i)->Process(this);
    }
}

void MenuSetupItemsFactory::ProcessSystemMenuNode(SystemMenuNode* node)
{
    string text = "(S) " + node->State().Name();
    _osdMenu->Add(new cOsdItem(text.c_str()));
}

void MenuSetupItemsFactory::ProcessPluginMenuNode(PluginMenuNode* node)
{
    string text = "(P) " + node->PluginName();
    _osdMenu->Add(new cOsdItem(text.c_str()));
}

void MenuSetupItemsFactory::ProcessSubMenuNode(SubMenuNode* node)
{
    string text = "(M) " + node->Text();
    _osdMenu->Add(new cOsdItem(text.c_str()));
}

void MenuSetupItemsFactory::ProcessCommandMenuNode(CommandMenuNode* node)
{
    string text = "(C) " + node->Text();
    _osdMenu->Add(new cOsdItem(text.c_str()));
}

void MenuSetupItemsFactory::ProcessSeparatorMenuNode(SeparatorMenuNode* node)
{
    string text = (string) "(-) " + node->DisplayText();
    _osdMenu->Add(new cOsdItem(text.c_str()));
}
