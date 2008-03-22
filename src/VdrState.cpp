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

#include "VdrState.h"

using namespace std;

list<VdrState> VdrState::_availableStates(VdrState::InitializeAvailableStates());

VdrState::VdrState(eOSState state, string name)
{
    _state = state;
    _name = name;
}

list<VdrState> VdrState::InitializeAvailableStates()
{
    list<VdrState> states;
    states.push_back(VdrState(osSchedule, "Schedule"));
    states.push_back(VdrState(osRecordings, "Recordings"));
    states.push_back(VdrState(osChannels, "Channels"));
    states.push_back(VdrState(osTimers, "Timers"));
    states.push_back(VdrState(osCommands, "Commands"));
    states.push_back(VdrState(osSetup, "Setup"));
    return states;
}

VdrState VdrState::ByName(std::string name)
{
    for (list<VdrState>::iterator i = _availableStates.begin(); i != _availableStates.end(); i++)
    {
        if ((*i).Name() == name)
        {
            return *i;
        }
    }

    throw "unknown state identifier: " + name;
}

string VdrState::Name()
{
    return _name;
}

eOSState VdrState::OSState()
{
    return _state;
}
