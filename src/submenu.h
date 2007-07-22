#ifndef ___SUBMENU_H
#define ___SUBMENU_H

class SubMenu : public cOsdMenu
{
    public:
        virtual eOSState ProcessKey(eKeys Key);
};

#endif
