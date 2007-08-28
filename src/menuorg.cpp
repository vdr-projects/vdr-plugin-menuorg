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

#include <vdr/plugin.h>
#include <vdr/config.h>
#include <vdr/tools.h>
#include <vdr/mainmenuitemsprovider.h>
#include <vector>
#include <iostream>
#include <string>
#include <getopt.h>
#include "version.h"
#include "menuorg.h"
#include "menusetup.h"
#include "menuconfiguration.h"
#include "mainmenuitemsprovider.h"
#include "i18n.h"
#include "pluginsetup.h"

using namespace std;

MenuOrgPlugin::MenuOrgPlugin(void)
{
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
    _customMenuShouldBeActive = true;
    _unconfiguredPluginsShouldBeIncluded = true;
    _hideMainMenuEntry = true;
    _flatMenuSetup = false;
    _subMenuProvider = NULL;
    _menuConfiguration = NULL;
}

MenuOrgPlugin::~MenuOrgPlugin()
{
    delete _subMenuProvider;
    delete _menuConfiguration;
}

const char* MenuOrgPlugin::Version(void)
{
    return VERSION;
}

const char* MenuOrgPlugin::Description(void)
{
    return tr("organize your Mainmenu");
}

const char* MenuOrgPlugin::MainMenuEntry(void)
{
    if(_hideMainMenuEntry)
        return NULL;
    else
        return tr("Menu-Organizer");
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
                configFile = optarg;
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
    if(configFile.empty())
        configFile = (string) ConfigDirectory() + "/menuorg.xml";

    _menuConfiguration = new MenuConfiguration(configFile);
    // TODO need handling of unloadable config File here!!!

    _subMenuProvider = new MainMenuItemsProvider(*_menuConfiguration);

    RegisterI18n(Phrases);

    return true;
}

cOsdObject *MenuOrgPlugin::MainMenuAction(void)
{
    // Perform the action when selected from the main VDR menu.
    return new cMenuOrgSetup(*_menuConfiguration, _flatMenuSetup);
}

cMenuSetupPage *MenuOrgPlugin::SetupMenu(void)
{
    // Return a setup menu in case the plugin supports one.
    return new PluginSetup(_customMenuShouldBeActive, _unconfiguredPluginsShouldBeIncluded, _hideMainMenuEntry, _flatMenuSetup, *_menuConfiguration);
}

bool MenuOrgPlugin::SetupParse(const char *Name, const char *Value)
{
    if (!strcasecmp(Name, PluginSetup::SetupName::CustomMenuActive))
    {
        _customMenuShouldBeActive = (atoi(Value) != 0);
    }
    else if(!strcasecmp(Name, PluginSetup::SetupName::UnconfiguredPluginsIncluded))
    {
        _unconfiguredPluginsShouldBeIncluded = (atoi(Value) != 0);
    }
    else if(!strcasecmp(Name, PluginSetup::SetupName::HideMainMenuEntry))
    {
        _hideMainMenuEntry = (atoi(Value) != 0);
    }
    else if(!strcasecmp(Name, PluginSetup::SetupName::MenuSetupStyle))
    {
        _flatMenuSetup = (atoi(Value) != 0);
    }
    else
        return false;

    return true;
}

bool MenuOrgPlugin::Service(const char *Id, void *Data)
{
    if (strcmp(Id, MENU_ITEMS_PROVIDER_SERVICE_ID) == 0 && _customMenuShouldBeActive) 
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
