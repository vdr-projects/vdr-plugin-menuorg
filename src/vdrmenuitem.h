#ifndef ___VDRMENUITEM_H
#define ___VDRMENUITEM_H

#include "menunode.h"
#include <vdr/osdbase.h>
#include <vdr/submenupatch.h>
#include <string>

class VdrMenuItem: public MenuNode
{
    private:
        std::string _itemText;
        eOSState _itemState;

    public:
        VdrMenuItem(std::string itemText, eOSState itemState);
        SubMenuPatch::IMainMenuItem* CreateMainMenuItem();
};

#endif
