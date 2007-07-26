#ifndef ___MENUNODE_H
#define ___MENUNODE_H

#include <vector>
#include <vdr/submenupatch.h>

class MenuNode;

typedef std::vector<MenuNode*> MenuNodeList;

class MenuNode
{
    private:
        MenuNode* _parent;
        MenuNodeList _childs;
        
    protected:
        void SetParent(MenuNode* parent);

    public:
        virtual ~MenuNode();
        MenuNode* Parent();
        MenuNodeList& Childs();
        MenuNode* AddChild(MenuNode* child);
        virtual SubMenuPatch::MainMenuItem* CreateMainMenuItem();
};

#endif
