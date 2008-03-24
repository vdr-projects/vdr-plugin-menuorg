#ifndef MENUITEMDEFINITION_H_
#define MENUITEMDEFINITION_H_

#include <vdr/mainmenuitemsprovider.h>

class MenuNode;

class MenuItemDefinition: public IMenuItemDefinition
{
    private:
        MenuNode* _menuNode;
        bool _isSelected;

    public:
        MenuItemDefinition(MenuNode* menuNode);
        MenuNode* AssignedMenuNode();
};


#endif
