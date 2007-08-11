#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>
#include "menunode.h"
#include "xmlmenu.h"

using namespace SubMenuPatch;

class SubMenuProvider: public ISubMenuProvider
{
    private:
        MenuNode* _rootMenu;
        MenuNode* _currentMenu;
        MainMenuItemsList _currentMainMenuItems;

    public:
        SubMenuProvider(MenuNode* rootMenu);
        virtual MainMenuItemsList* MainMenuItems();
        virtual void EnterRootMenu();
        virtual void EnterSubMenu(cOsdItem* item);
        virtual bool LeaveSubMenu();

    private:
        void ResetMainMenuItemsList();
};

#endif
