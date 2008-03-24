#include "MenuItemDefinition.h"
#include "MenuNode.h"

MenuItemDefinition::MenuItemDefinition(MenuNode* menuNode)
    :_menuNode(menuNode)
{
}

MenuNode* MenuItemDefinition::AssignedMenuNode()
{
    return _menuNode;
}
