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

#ifndef ___CHILDLOCKSERVICE_H
#define ___CHILDLOCKSERVICE_H

#include <vdr/keys.h>

class cChannel;
class cRecording;
class cPlugin;
class cTimer;
class cEvent;
class cOsdObject;

class IChildLockService
{
    public:
        static const char* ServiceId;

    public:
        virtual ~IChildLockService() {};
        virtual bool IsUnlocked() = 0;

        virtual bool IsMenuProtected(const char* MenuName) = 0;
        virtual bool IsChannelProtected(const cChannel* Channel) = 0;
        virtual bool IsRecordingProtected(const cRecording* Recording, const char* Name, const char* Base, bool isDirectory) = 0;
        virtual bool IsPluginProtected(cPlugin* Plugin) = 0;

        virtual bool IsMenuHidden(const char* MenuName) = 0;
        virtual bool IsPluginHidden(cPlugin* Plugin) = 0;
        virtual bool IsRecordingHidden(const cRecording* Recording, const char* Name, const char* Base, bool isDirectory) = 0;
};

const char* IChildLockService::ServiceId = "ChildLockService-v0.1::ChildLockService";

#endif
