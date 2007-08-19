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

#include "systemmenuitem.h"
#include <vdr/menuorgpatch.h>
#include "custommainmenuitem.h"

SystemMenuItem::SystemMenuItem(std::string itemText, eOSState itemState)
{
    _itemText = itemText;
    _itemState = itemState;
}

MenuOrgPatch::IMainMenuItem* SystemMenuItem::CreateMainMenuItem()
{
    if(_itemState != osUser1)
        return new CustomMainMenuItem(new cOsdItem(tr(_itemText.c_str()), _itemState));
    else
        return new CustomMainMenuItem(new cOsdItem(_itemText.c_str(), _itemState));
}