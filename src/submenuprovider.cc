#include "submenuprovider.h"
#include <vdr/plugin.h>
#include <iostream>

//using namespace std;

SubMenuProvider::SubMenuProvider()
{
	_OsdSet = false;
	_inSubMenu = false;

}

void SubMenuProvider::CreateTestMenus()
{

	// Mainmenu
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub menu1"), osUser1)));
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub menu2"), osUser1)));

	// Submenu 1
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Schedule"), osSchedule)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Timers"), osTimers)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Recordings"), osRecordings)));

	// Submenu 2
	_myOsdItems[2].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Setup"), osSetup)));
        if (Commands.Count())
            _myOsdItems[2].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Commands"), osCommands)));

}

MainMenuItemsList* SubMenuProvider::MainMenuItems()
{
	ResetMainMenuItemsList();

	if (_OsdSet == false)
	{
		// create testmenu´s
		CreateTestMenus();

		// set mainmenu
		_osdItems=_myOsdItems[0];

		_OsdSet=true;
	}
	else
	{
		if (_inSubMenu)
			_osdItems=_myOsdItems[1];
		else
			_osdItems=_myOsdItems[0];

		//_osdItems=_myOsdItemNext;
	}

    return &_osdItems;
}

void SubMenuProvider::ResetMainMenuItemsList()
{
    for( MainMenuItemsList::iterator i = _osdItems.begin(); i != _osdItems.end(); i++)
    {
       delete *i;
    }
    _osdItems.clear(); 
}

void SubMenuProvider::EnterSubMenu(cOsdItem* item)
{
	if (_inSubMenu == false)
		_inSubMenu = true;

/*
	for(int i=0; i<=2; i++)
	{

		for( MainMenuItemsList::iterator oMenuItem = _myOsdItems[i].begin(); i != _myOsdItems[i].end(); i++)
		{
			if (oMenuItem==item)
				isyslog("Item found\n");
		}
		// Suche nach dem nächsten Submenu und speichere es dann in _myOsdItemNext
	}
*/
}

bool SubMenuProvider::LeaveSubMenu()
{
    if (_inSubMenu)
    {
        _inSubMenu = false;
        return true;
    }
    else
    {
        return false;
    }
}
