/*
 * vdr-menuorg - A plugin for the Linux Video Disk Recorder
 * Copyright (C) 2007 Thomas Creutz, Tobias Grimm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: submenunode.cpp 5835 2007-08-19 21:45:51Z svntcreutz $
 *
 */

#include "commandmenunode.h"
#include <vdr/osdbase.h>
#include <vdr/interface.h>
#include <vdr/menu.h>
#include "osditemdefinition.h"
#include "childlock.h"

using namespace std;

CommandMenuNode::CommandMenuNode(string text, string command, bool confirm)
{
    _text = text;
    _command = command;
    _confirm = confirm;
}

IMenuItemDefinition* CommandMenuNode::CreateMenuItemDefinition()
{
    return new OsdItemDefinition(new cOsdItem(_text.c_str(), osUser2));
}

cOsdMenu* CommandMenuNode::Execute()
{
    bool confirmed = true;
    if (_confirm)
    {
        confirmed = Interface->Confirm((_text + '?').c_str());
    }
    if (confirmed)
    {
        Skins.Message(mtStatus, (_text + "...").c_str());
        string result = ExecuteCommand();
        Skins.Message(mtStatus, NULL);
        if (!result.empty())
        {
            return new cMenuText(_text.c_str(), result.c_str(), fontFix);
        }
    }
    return NULL;
}

string CommandMenuNode::ExecuteCommand()
{
    string result;
    dsyslog("executing command '%s'", _command.c_str());
    cPipe pipe;
    if (pipe.Open(_command.c_str(), "r"))
    {
        int c;
        while ((c = fgetc(pipe)) != EOF)
        {
            result += (char) c;
        }
        pipe.Close();
    }
    else
    {
        esyslog("ERROR: can't open pipe for command '%s'", _command.c_str());
    }
    return result;
}

bool CommandMenuNode::IsHidden()
{
    return ChildLock::IsMenuHidden(_text.c_str());
}
