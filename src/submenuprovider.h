#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>
#include "menunode.h"
#include "xmlmenu.h"

using namespace SubMenuPatch;

class SubMenuProvider: public ISubMenuProvider
{
    private:
        bool _someError;
        XmlMenu _oXmlMenu;
        MenuNode* _currentMenu;
        MainMenuItemsList _currentMainMenuItems;

    public:
        SubMenuProvider();
        virtual MainMenuItemsList* MainMenuItems();
        virtual void EnterRootMenu();
        virtual void EnterSubMenu(cOsdItem* item);
        virtual bool LeaveSubMenu();
        bool getSomeError();

    private:
        void ResetMainMenuItemsList();
        void CreateTestMenus();
};

#endif
