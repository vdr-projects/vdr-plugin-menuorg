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

#ifndef ___OSDXMLITEM_H
#define ___OSDXMLITEM_H

#include <string>
#include <vdr/menu.h>
#include <libxml++/libxml++.h>

using namespace std;
namespace xmlpp { class Element; }

class cOsdXmlItem: public cOsdItem
{
    public:
        const xmlpp::Element* _xmlElement;

        enum sItemType
        {
            SYSTEM = 0,
            PLUGIN = 1,
            MENU = 2,
            COMMAND = 3
        };

    private:
        sItemType _ItemType;
        string _nameAttribute;
        string _titleAttribute;
        string _commandAttribute;
        string _confirmAttribute;

    public:
        cOsdXmlItem(const char* Text, const xmlpp::Element* xmlElement, eOSState State=osUnknown);

        sItemType getItemType(void);
        string getNameAttribute(void);
        string getTitleAttribute(void);
        string getCommandAttribute(void);
        string getConfirmAttribute(void);

        void setItemType(sItemType type);
        void setNameAttribute(string name);
        void setTitleAttribute(string title);
        void setCommandAttribute(string command);
        void setConfirmAttribute(string confirm);

    private:
        void parseXmlElement(void); // parse the xml element and set the private attributes
};

#endif
