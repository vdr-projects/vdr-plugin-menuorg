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

#include <string>
#include <vdr/menu.h>
#include <libxml++/libxml++.h>
#include "osdxmlitem.h"

using namespace std;
using namespace xmlpp;

cOsdXmlItem::cOsdXmlItem(const char* Text, const xmlpp::Element* xmlElement, eOSState State=osUnknown)
: cOsdItem()
{
    _xmlElement = xmlElement;
    parseXmlElement();
}

void cOsdXmlItem::parseXmlElement(void)
{
    const Attribute* nameAttribute = _xmlElement->get_attribute("name");

    string type = _xmlElement->get_name();
    string name = nameAttribute->get_value();

    setNameAttribute(name);

    if (type == "system")
    {
        setItemType(SYSTEM);
        const Attribute* titleAttribute = _xmlElement->get_attribute("title");
        string title = titleAttribute ? (string) titleAttribute->get_value() : "";
        setTitleAttribute(title);
    }
    else if (type == "plugin")
    {
        setItemType(PLUGIN);
        const Attribute* titleAttribute = _xmlElement->get_attribute("title");
        string title = titleAttribute ? (string) titleAttribute->get_value() : "";
        setTitleAttribute(title);
    }
    else if ( type == "menu")
    {
        setItemType(MENU);
    }
    else if (type == "command")
    {
        setItemType(COMMAND);

        string execute = _xmlElement->get_attribute("execute")->get_value();
        setCommandAttribute(execute);

        const Attribute* confirmAttribute = _xmlElement->get_attribute("confirm");
        if (confirmAttribute)
            setConfirmAttribute(confirmAttribute->get_value());
    }
}

cOsdXmlItem::sItemType cOsdXmlItem::getItemType(void)
{
    return _ItemType;
}

string cOsdXmlItem::getNameAttribute(void)
{
    return _nameAttribute;
}

string cOsdXmlItem::getTitleAttribute(void)
{
    return _titleAttribute;
}

string cOsdXmlItem::getCommandAttribute(void)
{
    return _commandAttribute;
}

string cOsdXmlItem::getConfirmAttribute(void)
{
    return _confirmAttribute;
}

void cOsdXmlItem::setItemType(sItemType type)
{
    _ItemType = type;
}

void cOsdXmlItem::setNameAttribute(string name)
{
    _nameAttribute = name;
}

void cOsdXmlItem::setTitleAttribute(string title)
{
    _titleAttribute = title;
}

void cOsdXmlItem::setCommandAttribute(string command)
{
    _commandAttribute = command;
}

void cOsdXmlItem::setConfirmAttribute(string confirm)
{
    _confirmAttribute = confirm;
}
