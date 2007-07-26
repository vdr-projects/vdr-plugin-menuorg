#ifndef ___VDRMENUITEM_H
#define ___VDRMENUITEM_H

#include "menunode.h"
#include <vdr/osdbase.h>
#include <vdr/submenupatch.h>

class VdrMenuItem: public MenuNode
{
    private:
        const char* _itemText;
        eOSState _itemState;

    public:
        VdrMenuItem(const char* itemText, eOSState itemState);
        SubMenuPatch::MainMenuItem* CreateMainMenuItem();
};

#endif
