#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>

using namespace SubMenuPatch;

class SubMenuProvider: public ISubMenuProvider
{
    private:
        MainMenuItemsList _osdItems;

    public:
        virtual MainMenuItemsList* MainMenuItems();
        virtual cOsdMenu* OpenSubMenu(int mainMenuItemIndex);

    private:
         void ResetMainMenuItemsList();
};

#endif
