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

#include "SystemMenuNode.h"
#include "ChildLock.h"
#include "IMenuNodeProcessor.h"
#include <vdr/i18n.h>

using namespace std;

SystemMenuNode::SystemMenuNode(VdrState state, string customTitle)
    :_state(state)
{
    _customTitle = customTitle;
}

SystemMenuNode* SystemMenuNode::Clone()
{
    return new SystemMenuNode(*this);
}

bool SystemMenuNode::IsHidden()
{
    return ChildLock::IsMenuHidden(_state.Name().c_str());
}

void SystemMenuNode::Process(IMenuNodeProcessor* menuNodeProcessor)
{
    menuNodeProcessor->ProcessSystemMenuNode(this);
}

VdrState SystemMenuNode::State()
{
    return _state;
}

string SystemMenuNode::CustomTitle()
{
    return _customTitle;
}

string SystemMenuNode::DisplayText()
{
    if (_customTitle.empty())
    {
        return tr(_state.Name().c_str());
    }
    else
    {
        return _customTitle;
    }
}
