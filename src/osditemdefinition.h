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

#ifndef ___OSDITEMDEFINITION_H
#define ___OSDITEMDEFINITION_H

#include <vdr/mainmenuitemsprovider.h>

class OsdItemDefinition: public IMenuItemDefinition
{
    private:
        cOsdItem* _osdItem;

    public:
        OsdItemDefinition(cOsdItem* osdItem);
        virtual bool IsCustomOsdItem();
        virtual bool IsPluginItem();
        virtual cOsdItem* CustomOsdItem();
        virtual const char* PluginMenuEntry();
        virtual int PluginIndex();
};

#endif