#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>

using namespace SubMenuPatch;

class SubMenuProvider: public ISubMenuProvider
{
	private:
		MainMenuItemsList _osdItems;
		MainMenuItemsList _myOsdItems[5];
		MainMenuItemsList _myOsdItemNext;
		bool _OsdSet;
		bool _inSubMenu;

	public:
		SubMenuProvider();
		virtual MainMenuItemsList* MainMenuItems();
		virtual void EnterSubMenu(cOsdItem* item);
		virtual bool LeaveSubMenu();

	private:
		void ResetMainMenuItemsList();
		void CreateTestMenus();
};

#endif
