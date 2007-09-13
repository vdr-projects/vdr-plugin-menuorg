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

#include "XmlConfigurationFactory.h"
#include <libxml++/libxml++.h>
#include "SystemMenuNode.h"
#include "PluginMenuNode.h"
#include "SubMenuNode.h"
#include "CommandMenuNode.h"
#include "SeparatorMenuNode.h"

using namespace xmlpp;

Document* XmlConfigurationFactory::CreateXmlConfig(SubMenuNode* node)
{
    Document* doc = new Document();
    XmlConfigurationFactory xmlMenuNodeFactory(doc->create_root_node("menus"));
    for (MenuNodeList::iterator i = node->Childs()->begin(); i != node->Childs()->end(); i++)
    {
        (*i)->Process(&xmlMenuNodeFactory);
    }
    return doc;
}

void XmlConfigurationFactory::ProcessSystemMenuNode(SystemMenuNode* node)
{
    Element* systemNode = _parent->add_child("system");
    systemNode->set_attribute("name", node->State().Name());
    if (!node->CustomTitle().empty())
    {
        systemNode->set_attribute("title", node->CustomTitle());
    }
}

void XmlConfigurationFactory::ProcessPluginMenuNode(PluginMenuNode* node)
{
    Element* pluginNode = _parent->add_child("plugin");
    pluginNode->set_attribute("name", node->PluginName());
    if (!node->CustomTitle().empty())
    {
        pluginNode->set_attribute("title", node->CustomTitle());
    }
}

void XmlConfigurationFactory::ProcessSubMenuNode(SubMenuNode* node)
{
    Element* menuNode = _parent->add_child("menu");
    menuNode->set_attribute("name", node->Text());
    XmlConfigurationFactory subMenuFactory(menuNode);
    for (MenuNodeList::iterator i = node->Childs()->begin(); i != node->Childs()->end(); i++)
    {
        (*i)->Process(&subMenuFactory);
    }
}

void XmlConfigurationFactory::ProcessCommandMenuNode(CommandMenuNode* node)
{
    Element* commandNode = _parent->add_child("command");
    commandNode->set_attribute("name", node->Text());
    commandNode->set_attribute("execute", node->Command());
    commandNode->set_attribute("confirm", node->ShouldConfirm() ? "yes" : "no");
}

void XmlConfigurationFactory::ProcessSeparatorMenuNode(SeparatorMenuNode* node)
{
    Element* separatorNode = _parent->add_child("separator");
    separatorNode->set_attribute("title", node->CustomTitle());
}

XmlConfigurationFactory::XmlConfigurationFactory(Element* parent)
{
    _parent = parent;
}
