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

#include "PluginMenuNode.h"
#include <vdr/plugin.h>
#include "ChildLock.h"
#include "IMenuNodeProcessor.h"

using namespace std;

PluginMenuNode::PluginMenuNode(string pluginName, string customTitle)
{
    _customTitle = customTitle;
    _pluginName = pluginName;

    if (!FindPluginByName(pluginName, _plugin, _pluginIndex))
    {
        _plugin = NULL;
        _pluginIndex = -1;
    }

}

PluginMenuNode* PluginMenuNode::Clone()
{
    return new PluginMenuNode(*this);
}

string PluginMenuNode::CustomTitle()
{
    return _customTitle;
}

void PluginMenuNode::CustomTitle(string newCustomTitle)
{
    _customTitle = newCustomTitle;
}

string PluginMenuNode::PluginName()
{
    return _pluginName;
}

void PluginMenuNode::PluginName(string newPluginName)
{
    _pluginName = newPluginName;
    if (!FindPluginByName(newPluginName, _plugin, _pluginIndex))
    {
        _plugin = NULL;
        _pluginIndex = -1;
    }
}

bool PluginMenuNode::IsHidden()
{
    return (!HasMainMenuEntry()) || ChildLock::IsPluginHidden(_plugin);
}

bool PluginMenuNode::HasMainMenuEntry()
{
    return (_plugin && _plugin->MainMenuEntry());
}

void PluginMenuNode::Process(IMenuNodeProcessor* menuNodeProcessor)
{
    menuNodeProcessor->ProcessPluginMenuNode(this);
}

int PluginMenuNode::PluginIndex()
{
    return _pluginIndex;
}

bool PluginMenuNode::FindPluginByName(string name, cPlugin*& plugin, int& pluginIndex)
{
    int i = 0;

    while (cPlugin *currentPlugin = cPluginManager::GetPlugin(i))
    {
        if (name == currentPlugin->Name()) 
        {
            plugin = currentPlugin;
            pluginIndex = i;
            return true;
        }
        i++;
    }

    return false;
}

string PluginMenuNode::DisplayText()
{
    if (_customTitle.empty() && HasMainMenuEntry())
    {
        return _plugin->MainMenuEntry();
    }
    else
    {
        return _customTitle;
    }
}
