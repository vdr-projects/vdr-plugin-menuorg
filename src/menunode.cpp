#include "menunode.h"

MenuNode::MenuNode()
{
    _parent = NULL;
}

MenuNode::~MenuNode()
{
    while (!_childs.empty())
    {
        delete _childs.back();
        _childs.pop_back();
    }
}

MenuNode* MenuNode::Parent()
{
    return _parent;
}

MenuNodeList& MenuNode::Childs()
{
    return _childs;
}

MenuNode* MenuNode::AddChild(MenuNode* child)
{
    _childs.push_back(child);
    child->SetParent(this);
    return child;
}

void MenuNode::SetParent(MenuNode* parent)
{
    _parent = parent;
}

SubMenuPatch::IMainMenuItem* MenuNode::CreateMainMenuItem()
{
    return NULL;
}
