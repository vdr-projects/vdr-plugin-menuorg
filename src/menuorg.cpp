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
#include <vdr/menuorgpatch.h>
#include <vector>
#include <iostream>
#include <string>
#include <getopt.h>
#include "version.h"
#include "menuorg.h"
#include "i18n.h"

using namespace std;
using namespace MenuOrgPatch;

MenuOrgPlugin::MenuOrgPlugin(void)
{
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}

MenuOrgPlugin::~MenuOrgPlugin()
{
  // Clean up after yourself!
  delete _subMenuProvider;
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
    return NULL;
}

const char *MenuOrgPlugin::CommandLineHelp(void)
{
    return " -c FILE   --config=FILE   loads the specified xml file\n"
           "                           (default: ConfigDir/plugins/menuorg.xml)\n"
           " -s FILE   --schema=FILE   loads the specified schema file\n"
           "                           (default: ConfigDir/plugins/menuorg.dtd)\n";
}

bool MenuOrgPlugin::ProcessArgs(int argc, char *argv[])
{
    static struct option longOptions[] =
    {
        { "config", required_argument, NULL, 'c'},
        { "schema", required_argument, NULL, 's'},
        { NULL}
    };

    optind = 0;
    opterr = 0;

    int optionChar;
    int optionIndex = 0;
    while ((optionChar = getopt_long(argc, argv, "c:s:", longOptions, &optionIndex)) != -1)
    {
        switch (optionChar)
        {
            case 'c':
                configFile = optarg;
                break;

            case 's':
                schemaFile = optarg;
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
    XmlMenu xmlMenu;

    if(configFile.empty())
        configFile = (string) ConfigDirectory() + "/menuorg.xml";

    if(schemaFile.empty())
        schemaFile = (string) ConfigDirectory() + "/menuorg.dtd";

    MenuNode* menu = xmlMenu.LoadXmlMenu(configFile, schemaFile);
    if (menu)
    {
        _subMenuProvider = new MainMenuItemsProvider(menu);
    }
    else
    {
        _subMenuProvider = NULL;
    }

    RegisterI18n(Phrases);

    return true;
}

cOsdObject *MenuOrgPlugin::MainMenuAction(void)
{
    // Perform the action when selected from the main VDR menu.
    //TODO: when the MenuItem is called, than ask for reloading the xml-file
    return NULL;
}

cMenuSetupPage *MenuOrgPlugin::SetupMenu(void)
{
    // Return a setup menu in case the plugin supports one.
    return NULL;
}

bool MenuOrgPlugin::SetupParse(const char *Name, const char *Value)
{
    // Parse your own setup parameters and store their values.
    //TODO: move code for load the xml file to this position
    return false;
}

bool MenuOrgPlugin::Service(const char *Id, void *Data)
{
    if (strcmp(Id, "MenuOrgPatch-v0.1::MainMenuItemsProvider") == 0) 
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
