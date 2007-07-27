#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>
#include "menunode.h"
#include "xmlmenu.h"

using namespace SubMenuPatch;

class SubMenuProvider: public ISubMenuProvider
{
    private:
        XmlMenu _oXmlMenu;
        //MenuNode _rootMenuNode;
        MenuNode* _currentMenu;
        MainMenuItemsList _currentMainMenuItems;

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
