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

#ifndef ___SYSTEMMENUITEM_H
#define ___SYSTEMMENUITEM_H

#include "menunode.h"
#include <vdr/osdbase.h>
#include <string>

class SystemMenuItem: public MenuNode
{
    private:
        std::string _itemText;
        eOSState _itemState;

    public:
        SystemMenuItem(std::string itemText, eOSState itemState);
        MenuOrgPatch::IMainMenuItem* CreateMainMenuItem();
};

#endif
