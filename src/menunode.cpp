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

#include "menunode.h"

MenuNode::MenuNode()
{
    _parent = NULL;
}

MenuNode::~MenuNode()
{
    while (!_childs.empty())
    {
        delete _childs.back();
        _childs.pop_back();
    }
}

MenuNode* MenuNode::Parent()
{
    return _parent;
}

MenuNodeList& MenuNode::Childs()
{
    return _childs;
}

MenuNode* MenuNode::AddChild(MenuNode* child)
{
    _childs.push_back(child);
    child->SetParent(this);
    return child;
}

void MenuNode::SetParent(MenuNode* parent)
{
    _parent = parent;
}

MenuOrgPatch::IMainMenuItem* MenuNode::CreateMainMenuItem()
{
    return NULL;
}
