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

#include "CommandMenuNode.h"
#include <vdr/interface.h>
#include <vdr/menu.h>
#include "ChildLock.h"
#include "IMenuNodeProcessor.h"

using namespace std;

CommandMenuNode::CommandMenuNode(string text, string command, bool confirm)
{
    _text = text;
    _command = command;
    _confirm = confirm;
}

CommandMenuNode* CommandMenuNode::Clone()
{
    return new CommandMenuNode(*this);
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

void CommandMenuNode::Process(IMenuNodeProcessor* menuNodeProcessor)
{
    menuNodeProcessor->ProcessCommandMenuNode(this);
}

string CommandMenuNode::Command()
{
    return _command;
}

void CommandMenuNode::Command(string newCommand)
{
    _command = newCommand;
}

bool CommandMenuNode::ShouldConfirm()
{
    return _confirm;
}

void CommandMenuNode::ShouldConfirm(bool newConfirm)
{
    _confirm = newConfirm;
}

string CommandMenuNode::Text()
{
    return _text;
}

void CommandMenuNode::Text(string newText)
{
    _text = newText;
}
