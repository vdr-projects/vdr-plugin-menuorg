#include "submenuprovider.h"
#include <vdr/plugin.h>
#include <iostream>

//using namespace std;

SubMenuProvider::SubMenuProvider()
{
	_OsdSet = false;
	_inSubMenu = false;
	_MenuIndex=0;

}

void SubMenuProvider::CreateTestMenus()
{

	// Mainmenu
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub menu1"), osUser1)));
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub menu2"), osUser1)));
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Setup"), osSetup)));
	if (Commands.Count())
		_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Commands"), osCommands)));

	_MenuZuordnung[0][0] = 1;
	_MenuZuordnung[0][1] = 2;
	_MenuZuordnung[0][2] = 0;
	_MenuZuordnung[0][3] = 0;

	// Submenu 1
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Schedule"), osSchedule)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Timers"), osTimers)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Recordings"), osRecordings)));

	_MenuZuordnung[1][0] = 1;
	_MenuZuordnung[1][1] = 1;
	_MenuZuordnung[1][2] = 1;
	_MenuZuordnung[1][3] = 1;
	_MenuZuordnung[1][4] = 1;

	int MenuCount = 0;
	// Submenu 2
	for (int i = 0; ; i++)
	{
		cPlugin *p = cPluginManager::GetPlugin(i);
		if (p)
		{
			const char *item = p->MainMenuEntry();
			if (item)
			{
				_myOsdItems[2].push_back(MainMenuItem::CreatePluginMenuItem(item, i));
				_MenuZuordnung[2][MenuCount] = 2;
			}
		}
		else
			break;
	}

}

MainMenuItemsList* SubMenuProvider::MainMenuItems()
{
	isyslog("Call MainMenuItems - _MenuIndex=%d", _MenuIndex);

	ResetMainMenuItemsList();

	if (_OsdSet == false)
	{
		// create testmenu´s
		CreateTestMenus();

		// set mainmenu
		_osdItems=_myOsdItems[_MenuIndex];
		
		_OsdSet=true;
	}
	else
	{
		_osdItems=_myOsdItems[_nextMenuIndex];
		_MenuIndex=_nextMenuIndex;
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
	isyslog("Call EnterSubMenu - _MenuIndex=%d", _MenuIndex);
	unsigned int itemIndex;

	for(itemIndex=0; itemIndex < _osdItems.size(); itemIndex++)
	{
		MainMenuItem* menuItem = _osdItems.at(itemIndex);
		if (menuItem->IsCustomMenuItem() && (menuItem->CustomMenuItem() == item))
		{
			break;
		}
	}

	_nextMenuIndex = _MenuZuordnung[_MenuIndex][itemIndex];
}

bool SubMenuProvider::LeaveSubMenu()
{
	isyslog("Call LeaveSubMenu - _MenuIndex=%d", _MenuIndex);

    if (_MenuIndex != 0)
    {
	_MenuIndex = 0;
        return true;
    }
    else
    {
        return false;
    }
}
