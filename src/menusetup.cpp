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
#include "menuconfiguration.h"
#include "menuitemsetup.h"
#include <vdr/menu.h>
#include <vdr/interface.h>
#include <libxml++/libxml++.h>
#include <iostream>

using namespace xmlpp;
using namespace std;

cMenuOrgSetup::cMenuOrgSetup(MenuConfiguration& menuConfiguration, bool flatMenuSetup)
:cOsdMenu(tr("Menu Setup")),_menuConfiguration(menuConfiguration)
{
    _flatMenuSetup = flatMenuSetup;
    CreateMenuItems(_menuConfiguration.Configuration(), 0);
}

void cMenuOrgSetup::CreateMenuItems(const Element* menuRoot, int iCount)
{
    int cur=Current();

    if(iCount == 0) 
        Clear();

    Node::NodeList children = menuRoot->get_children();
    for (Node::NodeList::iterator i = children.begin(); i != children.end(); i++)
    {
        const Element* childElement = dynamic_cast<const Element*>(*i);

        if (childElement)
        {
            const Attribute* nameAttribute = childElement->get_attribute("name");

            string type = childElement->get_name();
            string name = nameAttribute->get_value();

            for (int i=0; i <= iCount ;i++)
                name = " " + name;

            if ( type == "menu" && _flatMenuSetup)
            {
                name = "+" + name;
                Add(new cOsdItem(name.c_str()), true);
                CreateMenuItems(childElement, iCount+1);
            }
            else
            {
                if(iCount > 0)
                    name = "  " + name;

                Add(new cOsdItem(name.c_str()), true);
            }
        }
    }
    if(iCount == 0)
    {
        SetCurrent(Get(cur));
        Display();
        DrawButton();
    }
}

eOSState cMenuOrgSetup::ProcessKey(eKeys Key)
{
    dsyslog("menuorg: cMenuSetup::ProcessKey called");
    std::cerr << "menuorg: cMenuSetup::ProcessKey called" << std::endl;

    eOSState state = cOsdMenu::ProcessKey(Key);

    if(HasSubMenu())
    {
        return state;
    }
    if(state == osUnknown)
    {
        switch(Key)
        {
                case kRed:
                    DrawButton();
                    break;
    
                case kGreen:
                    state = AddSubMenu(new cMenuItemSetup());
                    break;
    
                case kYellow:
                    DrawButton();
                    break;
    
                case kBlue:
                    DrawButton();
                    break;
    
                case kUp:
                case kDown:
                case kLeft:
                    DrawButton();
                    break;
    
                case kOk:
                    if (Interface->Confirm(tr("Apply Changes?")))
                    {
                            // Save it!
                    }
                    return osEnd;
                    break;
    
                case kBack :
                    return osBack;
                    break;
    
                default: 
                    DrawButton();
                    break;
        }
    }
    return state;
}

void cMenuOrgSetup::DrawButton(void)
{
    SetHelp(tr("Create"),tr("Edit"),tr("Delete"),tr("Move"));
    Display();
}
