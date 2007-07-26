#include "submenuprovider.h"
#include <vdr/plugin.h>
#include <iostream>

//using namespace std;

SubMenuProvider::SubMenuProvider()
{
	_MenuIndex=0;
	_nextMenuIndex=0;
	CreateTestMenus();
}

void SubMenuProvider::CreateTestMenus()
{
	// Mainmenu
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub menu1"), osUser1)));
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub menu2"), osUser1)));
	_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Setup"), osSetup)));
	if (Commands.Count())
		_myOsdItems[0].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Commands"), osCommands)));

	_MenuSwitch[0][0][ENTER] = 1;
	_MenuSwitch[0][0][LEAVE] = 0;

	_MenuSwitch[0][1][ENTER] = 2;
	_MenuSwitch[0][1][LEAVE] = 0;

	_MenuSwitch[0][2][ENTER] = 0;
	_MenuSwitch[0][2][LEAVE] = 0;

	_MenuSwitch[0][3][ENTER] = 0;
	_MenuSwitch[0][3][LEAVE] = 0;

	// Submenu 1
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Schedule"), osSchedule)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Timers"), osTimers)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Recordings"), osRecordings)));
	_myOsdItems[1].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("A custom sub sub menu1"), osUser1)));

	_MenuSwitch[1][0][ENTER] = 1;
	_MenuSwitch[1][0][LEAVE] = 0;

	_MenuSwitch[1][1][ENTER] = 1;
	_MenuSwitch[1][1][LEAVE] = 0;

	_MenuSwitch[1][2][ENTER] = 1;
	_MenuSwitch[1][2][LEAVE] = 0;

	_MenuSwitch[1][3][ENTER] = 1;
	_MenuSwitch[1][3][LEAVE] = 0;

	_MenuSwitch[1][4][ENTER] = 3;
	_MenuSwitch[1][4][LEAVE] = 0;

	// Submenu 2
	int MenuItemCount = 0;
	for (int i = 0; ; i++)
	{
		cPlugin *p = cPluginManager::GetPlugin(i);
		if (p)
		{
			const char *item = p->MainMenuEntry();
			if (item)
			{
				_myOsdItems[2].push_back(MainMenuItem::CreatePluginMenuItem(item, i));
				_MenuSwitch[2][MenuItemCount][ENTER] = 2;
				_MenuSwitch[2][MenuItemCount][LEAVE] = 0;
				MenuItemCount++;
			}
		}
		else
			break;
	}

	// Sub Sub Menu 1
	_myOsdItems[3].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("a Test Item"), osContinue)));
	_myOsdItems[3].push_back(MainMenuItem::CreateCustomMenuItem(new cOsdItem(tr("Channels"), osChannels)));
	_MenuSwitch[3][0][ENTER] = 3;
	_MenuSwitch[3][0][LEAVE] = 1;
	_MenuSwitch[3][0][ENTER] = 3;
	_MenuSwitch[3][0][LEAVE] = 1;
}

MainMenuItemsList* SubMenuProvider::MainMenuItems()
{
	isyslog("Call MainMenuItems() - _MenuIndex=%d - _nextMenuIndex=%d", _MenuIndex, _nextMenuIndex);

	ResetMainMenuItemsList();

	_osdItems=_myOsdItems[_nextMenuIndex];
	_MenuIndex=_nextMenuIndex;

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
	isyslog("Call EnterSubMenu() - _MenuIndex=%d", _MenuIndex);

	unsigned int itemIndex;

	for(itemIndex=0; itemIndex < _osdItems.size(); itemIndex++)
	{
		MainMenuItem* menuItem = _osdItems.at(itemIndex);
		if (menuItem->IsCustomMenuItem() && (menuItem->CustomMenuItem() == item))
		{
			break;
		}
	}
	isyslog("_MenuSwitch[%d][%d][ENTER]=%d",_MenuIndex,itemIndex,_MenuSwitch[_MenuIndex][itemIndex][ENTER]);
	_nextMenuIndex = _MenuSwitch[_MenuIndex][itemIndex][ENTER];
}

bool SubMenuProvider::LeaveSubMenu()
{
	isyslog("Call LeaveSubMenu() - _MenuIndex=%d", _MenuIndex);
	
	if (_MenuIndex != _MenuSwitch[_MenuIndex][0][LEAVE])
	{
		_nextMenuIndex = _MenuSwitch[_MenuIndex][0][LEAVE];
		isyslog("LeaveSubMenu() - return true");
		return true;
	}
	else
	{
		isyslog("LeaveSubMenu() - return false");
		return false;
	}
}
