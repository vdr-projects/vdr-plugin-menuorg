/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (c) 2007 - 2008 Tobias Grimm <vdr@e-tobi.net>
 * Copyright (c) 2007        Thomas Creutz <thomas.creutz@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * $Id$
 *
 */

#include "ChildLock.h"
#include <vdr/plugin.h>
#include "IChildLockService.h"

IChildLockService* ChildLock::_childLockService = NULL;

bool ChildLock::IsMenuHidden(const char* MenuName)
{
    if (IChildLockService* childLockService = ChildLockService())
    {
        return childLockService->IsMenuHidden(MenuName);
    }
    else
    {
        return false;
    }
}

bool ChildLock::IsPluginHidden(cPlugin* Plugin)
{
    if (IChildLockService* childLockService = ChildLockService())
    {
        return childLockService->IsPluginHidden(Plugin);
    }
    else
    {
        return false;
    }
}

IChildLockService* ChildLock::ChildLockService()
{
    if (!_childLockService)
    {
        IChildLockService* childLockService;

        if (cPluginManager::CallFirstService(IChildLockService::ServiceId, &childLockService))
        {
            _childLockService = childLockService;
        }
        else
        {
            _childLockService = NULL;
        }
    }

    return _childLockService;
}
