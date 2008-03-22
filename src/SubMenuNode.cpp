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

void SubMenuNode::Text(string newText)
{
    _text = newText;
}

bool SubMenuNode::IsHidden()
{
    return ChildLock::IsMenuHidden(_text.c_str());
}

void SubMenuNode::Process(IMenuNodeProcessor* menuNodeProcessor)
{
    menuNodeProcessor->ProcessSubMenuNode(this);
}
