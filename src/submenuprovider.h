#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>

using namespace SubMenuPatch;

class SubMenuProvider: public ISubMenuProvider
{
    private:
        MainMenuItemsList _osdItems;
        bool _inSubMenu;

    public:
        SubMenuProvider();
        virtual MainMenuItemsList* MainMenuItems();
        virtual void EnterSubMenu(int mainMenuItemIndex);
        virtual bool LeaveSubMenu();

    private:
         void ResetMainMenuItemsList();
};

#endif
