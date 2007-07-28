#include "vdrmenuitem.h"
#include <vdr/submenupatch.h>
#include "custommainmenuitem.h"

VdrMenuItem::VdrMenuItem(std::string itemText, eOSState itemState)
{
    _itemText = itemText;
    _itemState = itemState;
}

SubMenuPatch::IMainMenuItem* VdrMenuItem::CreateMainMenuItem()
{
    return new CustomMainMenuItem(new cOsdItem(tr(_itemText.c_str()), _itemState));
}
