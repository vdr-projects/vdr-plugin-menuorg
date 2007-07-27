#ifndef ___SUBMENUITEM_H
#define ___SUBMENUITEM_H

#include "vdrmenuitem.h"
#include <string>

class SubMenuItem: public VdrMenuItem
{
    public:
        SubMenuItem(std::string itemText);
};

#endif
