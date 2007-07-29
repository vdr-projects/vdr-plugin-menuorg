/*
 * vdr-submenu - A plugin for the Linux Video Disk Recorder
 * Copyright (c) 2007 Tobias Grimm <vdr@e-tobi.net>
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

#include "custommainmenuitem.h"

CustomMainMenuItem::CustomMainMenuItem(cOsdItem* osdItem)
{
    _osdItem = osdItem;
}

bool CustomMainMenuItem::IsCustomMenuItem()
{
    return true;
}

bool CustomMainMenuItem::IsPluginMenuItem()
{
    return false;
}

cOsdItem* CustomMainMenuItem::CustomMenuItem()
{
    return _osdItem; 
}

const char* CustomMainMenuItem::PluginMenuEntry()
{
    return NULL;
}

int CustomMainMenuItem::PluginIndex()
{
    return 0;
}