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

#include "SubMenuNode.h"
#include "ChildLock.h"
#include "IMenuNodeProcessor.h"

using namespace std;

SubMenuNode::SubMenuNode(string text)
{
    _text = text;
}

SubMenuNode::~SubMenuNode()
{
    while (!_childs.empty())
    {
        delete _childs.back();
        _childs.pop_back();
    }
}

SubMenuNode* SubMenuNode::Clone()
{
    SubMenuNode* clone = new SubMenuNode(*this);
    clone->Childs()->clear();
    for (MenuNodeList::iterator i = _childs.begin(); i != _childs.end(); i++)
    {
        (*i)->Clone()->AddToParent(clone);
    }
    return clone;
}

MenuNodeList* SubMenuNode::Childs()
{
    return &_childs;
}

MenuNode* SubMenuNode::AddChild(MenuNode* child)
{
    child->AddToParent(this);
    return child;
}

string SubMenuNode::Text()
{
    return _text;
}

bool SubMenuNode::IsHidden()
{
    return ChildLock::IsMenuHidden(_text.c_str());
}

void SubMenuNode::Process(IMenuNodeProcessor* menuNodeProcessor)
{
    menuNodeProcessor->ProcessSubMenuNode(this);
}
