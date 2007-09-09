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

#ifndef ___MENUORGPLUGIN_H
#define ___MENUORGPLUGIN_H

#include <vdr/plugin.h>
#include <string>
#include "PluginConfiguration.h"

class MainMenuItemsProvider;
class MenuConfigurationRepository;

class MenuOrgPlugin : public cPlugin
{
    private:
        MainMenuItemsProvider* _subMenuProvider;
        std::string _configFile;
        PluginConfiguration _pluginConfiguration;
        MenuConfigurationRepository* _menuConfigurationRepository;

    public:
        MenuOrgPlugin(void);
        virtual ~MenuOrgPlugin();
        virtual const char* Version(void);
        virtual const char* Description(void);
        virtual const char* CommandLineHelp(void);
        virtual bool ProcessArgs(int argc, char* argv[]);
        virtual bool Initialize(void);
        virtual const char* MainMenuEntry(void);
        virtual cOsdObject* MainMenuAction(void);
        virtual cMenuSetupPage *SetupMenu(void);
        virtual bool SetupParse(const char* Name, const char* Value);
        virtual bool Service(const char* Id, void* Data = NULL);
};

extern "C" void* VDRPluginCreator();

#endif
