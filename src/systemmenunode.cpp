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

#include "systemmenunode.h"
#include <vdr/mainmenuitemsprovider.h>
#include "osditemdefinition.h"
#include "childlock.h"

SystemMenuNode::SystemMenuNode(std::string text, eOSState state)
{
    _text = text;
    _state = state;
}

IMenuItemDefinition* SystemMenuNode::CreateMenuItemDefinition()
{
    return new OsdItemDefinition(new cOsdItem(tr(_text.c_str()), _state));
}

bool SystemMenuNode::IsHidden()
{
    return ChildLock::IsMenuHidden(_text.c_str());
}
