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

#include "menusetup.h"
#include <vdr/menu.h>
#include <libxml++/libxml++.h>
#include "menuconfiguration.h"

using namespace xmlpp;
using namespace std;

cMenuSetup::cMenuSetup(MenuConfiguration& menuConfiguration)
:cOsdMenu(tr("MENU"),25),_menuConfiguration(menuConfiguration)
{
    //TODO
    
    Element* root = _menuConfiguration.Configuration();
    
    Node::NodeList children = root->get_children();
    for (Node::NodeList::iterator i = children.begin(); i != children.end(); i++)
    {
        const Element* childElement = dynamic_cast<const Element*>(*i);

        if (childElement)
        {
            const Attribute* nameAttribute = childElement->get_attribute("name");

            string type = childElement->get_name();
            string name = nameAttribute->get_value();
            
            Add(new cOsdItem(name.c_str(), osUser1));
        }
    }
}

eOSState cMenuSetup::ProcessKey(eKeys Key)
{
    eOSState state=cOsdMenu::ProcessKey(Key);
    if(state==osUnknown && Key==kOk) state=osBack;
    return state;
}
