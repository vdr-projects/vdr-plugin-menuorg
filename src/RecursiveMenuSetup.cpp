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
 * $Id: menusetup.cpp 6104 2007-08-28 22:38:14Z svntcreutz $
 *
 */

#include "RecursiveMenuSetup.h"
#include "menunode.h"
#include <string>
#include "commandmenunode.h"
#include "pluginmenunode.h"
#include "systemmenunode.h"
#include "submenunode.h"
#include "linemenunode.h"
#include <vdr/interface.h>

using namespace std;

class MenuSetupItemsFactory: IMenuNodeProcessor
{
private:
	cOsdMenu* _osdMenu;

public:
	MenuSetupItemsFactory(cOsdMenu* osdMenu)
	{
		_osdMenu = osdMenu;
	}
	
	void SetupItems(MenuNode& rootMenu)
	{
	    for (MenuNodeList::iterator i = rootMenu.Childs()->begin(); i != rootMenu.Childs()->end(); i++)
	    {
	        (*i)->Process(this);
	    }
	}

	// IMenuNodeProcessor
	void ProcessSystemMenuNode(SystemMenuNode* node)
	{
		string text = "(C) " + node->Text();
		_osdMenu->Add(new cOsdItem(text.c_str()));		
	}

	void ProcessPluginMenuNode(PluginMenuNode* node)
    {
		string text = "(P) " + node->Title();
		_osdMenu->Add(new cOsdItem(text.c_str()));
    }

    void ProcessSubMenuNode(SubMenuNode* node)
    {
    	string text = "(M) " + node->Text();
    	_osdMenu->Add(new cOsdItem(text.c_str()));
    }
    
    void ProcessCommandMenuNode(CommandMenuNode* node)
    {
    	string text = "(S) " + node->Text();
    	_osdMenu->Add(new cOsdItem(text.c_str()));
    }
    
    void ProcessLineMenuNode(LineMenuNode* node)
    {
    	string text = (string) "(L) " + "------------------";
    	_osdMenu->Add(new cOsdItem(text.c_str()));
    }
};

class MenuEditMenusFactory: IMenuNodeProcessor
{
private:
	cOsdMenu*& _menu;
	
public:
	static cOsdMenu* Create(MenuNode& menuNode)
	{
		cOsdMenu* menu = NULL;
		MenuEditMenusFactory editMenusFactory(menu);
		menuNode.Process(&editMenusFactory);
		return menu;
	}

	// IMenuNodeProcessor
	void ProcessSystemMenuNode(SystemMenuNode* node)
	{
		_menu = new cOsdMenu("Edit System Menu Node");
	}

	void ProcessPluginMenuNode(PluginMenuNode* node)
    {
		_menu = new cOsdMenu("Edit Plugin Menu Node");
    }

    void ProcessSubMenuNode(SubMenuNode* node)
    {
		_menu = new cOsdMenu("Edit Sub Menu Node");
    }
    
    void ProcessCommandMenuNode(CommandMenuNode* node)
    {
		_menu = new cOsdMenu("Edit Command Menu Node");
    }
    
    void ProcessLineMenuNode(LineMenuNode* nod)
    {
    	_menu = NULL;
    }

private:
	MenuEditMenusFactory(cOsdMenu*& menu)
		:_menu(menu)
	{
	}
};

RecursiveMenuSetup::RecursiveMenuSetup(MenuNode& rootMenu)
    :cOsdMenu(tr("Menu Configuration")), _rootMenu(rootMenu)
{
	_moving = false;
	CreateMenuItems();
	ShowHelp();
}

RecursiveMenuSetup::~RecursiveMenuSetup()
{
}

void RecursiveMenuSetup::CreateMenuItems()
{
	MenuSetupItemsFactory menuItemSetupFactory(this);
	menuItemSetupFactory.SetupItems(_rootMenu);
}

eOSState RecursiveMenuSetup::ProcessKey(eKeys Key)
{
	
   	if (_moving && ((Key == kUp) || (Key == kDown)))
    {
   		return MoveCurrentItem(Key == kUp);
    }

    eOSState state = cOsdMenu::ProcessKey(Key);

    if(HasSubMenu())
    {
        return state;
    }

    if ((state == osUnknown) && SelectedItem())
    {
        switch(Key)
        {
            case kOk:
            	if (_moving)
            	{
            		StopMoving();
            		return osContinue;
            	}
            	else
            	{
            		return ShowSubOrEditMenuForSelectedItem();
            	}
            	break;
            case kRed:
            	if (!_moving) StartMoving();
            	break;
            case kBlue:
            	return ShowEditMenuForSelectedItem();
            default: 
                break;
        }
    }
    return state;
}

void RecursiveMenuSetup::StartMoving()
{
	_moving = true;
	SetStatus("Move with Up/Down and confirm with OK");
	SetHelp(NULL);
}

void RecursiveMenuSetup::StopMoving()
{
	_moving = false;
	SetStatus(NULL);
	ShowHelp();
}

eOSState RecursiveMenuSetup::MoveCurrentItem(bool moveUp)
{
	int oldPos = Current();
	int newPos = Current();

	MenuNode* node = _rootMenu.Childs()->at(oldPos);

	if ((oldPos > 0) && (oldPos < Count()))
	{
		if (moveUp)
		{
			newPos = oldPos - 1;
		}
		else
		{
			newPos = oldPos + 1;
		}

		_rootMenu.Childs()->erase(_rootMenu.Childs()->begin() + oldPos);
		_rootMenu.Childs()->insert(_rootMenu.Childs()->begin() + newPos, node);

		Clear();
		CreateMenuItems();
		SetCurrent(Get(newPos));
		Display();
    }

	return osContinue;
}

void RecursiveMenuSetup::ShowHelp()
{
	SetHelp("Move", "Delete", "New", "Edit");
}

eOSState RecursiveMenuSetup::ShowEditMenuForSelectedItem()
{
	cOsdMenu* editMenu = MenuEditMenusFactory::Create(*SelectedItem());
	if (editMenu)
	{
		return AddSubMenu(editMenu);
	}
	else
	{
		return osContinue;
	}
}

MenuNode* RecursiveMenuSetup::SelectedItem()
{
	return _rootMenu.Childs()->at(Current());
}

eOSState RecursiveMenuSetup::ShowSubOrEditMenuForSelectedItem()
{
	if (!SelectedItem()->IsLeaf())
	{
   		return  AddSubMenu(new RecursiveMenuSetup(*SelectedItem()));
	}
	else
	{
		return ShowEditMenuForSelectedItem();
	}
}
