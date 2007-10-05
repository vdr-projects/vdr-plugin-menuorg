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
 * $Id$
 *
 */

#ifndef ___COMMANDMENUNODE_H
#define ___COMMANDMENUNODE_H

#include "MenuNode.h"
#include <string>

class IMenuNodeProcessor;

class CommandMenuNode: public MenuNode
{
    private:
        std::string _text;
        std::string _command;
        bool _confirm;

    public:
        CommandMenuNode(std::string text, std::string _command, bool confirm);
        std::string Text();
        void Text(std::string newText);
        std::string Command();
        void Command(std::string newCommand);
        bool ShouldConfirm();
        void ShouldConfirm(bool newConfirm);

        // MenuNode
        virtual void Process(IMenuNodeProcessor* menuNodeProcessor);
        bool IsHidden();
        cOsdMenu* Execute();
        CommandMenuNode* Clone();

    private:
        std::string ExecuteCommand();
};

#endif
