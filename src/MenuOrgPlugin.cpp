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

#include <vdr/plugin.h>
#include <vdr/config.h>
#include <vdr/tools.h>
#include <vdr/mainmenuitemsprovider.h>
#include <vector>
#include <iostream>
#include <string>
#include <getopt.h>
#include "Version.h"
#include "MenuOrgPlugin.h"
#include "MenuConfigurationRepository.h"
#include "MainMenuItemsProvider.h"
#include "PluginSetup.h"

using namespace std;

MenuOrgPlugin::MenuOrgPlugin(void)
{
    // Initialize any member variables here.
    // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
    // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!

    _subMenuProvider = NULL;
}

MenuOrgPlugin::~MenuOrgPlugin()
{
    delete _subMenuProvider;
    delete _menuConfigurationRepository;
}

const char* MenuOrgPlugin::Version(void)
{
    return VERSION;
}

const char* MenuOrgPlugin::Description(void)
{
    return tr("Reorganizes the main menu");
}

const char* MenuOrgPlugin::MainMenuEntry(void)
{
    return NULL;
}

const char *MenuOrgPlugin::CommandLineHelp(void)
{
    return " -c FILE   --config=FILE   loads the specified xml file\n"
           "                           (default: ConfigDir/plugins/menuorg.xml)\n";
}

bool MenuOrgPlugin::ProcessArgs(int argc, char *argv[])
{
    static struct option longOptions[] =
    {
        { "config", required_argument, NULL, 'c'},
        { NULL}
    };

    optind = 0;
    opterr = 0;

    int optionChar;
    int optionIndex = 0;
    while ((optionChar = getopt_long(argc, argv, "c:", longOptions, &optionIndex)) != -1)
    {
        switch (optionChar)
        {
            case 'c':
                _configFile = optarg;
                break;

            default:
                cerr << argv[0] << ": " << "invalid option " <<  argv[optind-1] << endl;
                return false;
        }
    }
    return true;
}

bool MenuOrgPlugin::Initialize(void)
{
    if (_configFile.empty())
    {
        _configFile = (string) ConfigDirectory() + "/menuorg.xml";
    }

    _menuConfigurationRepository = new MenuConfigurationRepository(_configFile);

    _subMenuProvider = new MainMenuItemsProvider(*_menuConfigurationRepository, _pluginConfiguration);

    return true;
}

cMenuSetupPage *MenuOrgPlugin::SetupMenu(void)
{
    _menuConfigurationRepository->Reset();
    return new PluginSetup(_pluginConfiguration, *_menuConfigurationRepository);
}

bool MenuOrgPlugin::SetupParse(const char *Name, const char *Value)
{
    return _pluginConfiguration.SetConfigurationOptionByName(Name, Value);
}

bool MenuOrgPlugin::Service(const char *Id, void *Data)
{
    if (strcmp(Id, MENU_ITEMS_PROVIDER_SERVICE_ID) == 0 && _pluginConfiguration.CustomMenuActive()) 
    {
        if (_subMenuProvider)
        {
            IMainMenuItemsProvider** ptr = (IMainMenuItemsProvider**)Data;
            *ptr = _subMenuProvider;

            return true;
        }
        else
        {
            Skins.Message(mtError, tr("Failed to load MenuOrg's config file!"));
        }
    }

    return false;
}
