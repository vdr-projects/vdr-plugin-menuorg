#include "vdrmenuitem.h"
#include <vdr/submenupatch.h>

VdrMenuItem::VdrMenuItem(const char* itemText, eOSState itemState)
{
    _itemText = itemText;
    _itemState = itemState;
}

SubMenuPatch::MainMenuItem* VdrMenuItem::CreateMainMenuItem()
{
    return SubMenuPatch::MainMenuItem::CreateCustomMenuItem(
      new cOsdItem(_itemText, _itemState));
}
