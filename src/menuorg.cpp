/*
 * menuorg.cpp: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

#include <vdr/plugin.h>
#include <vdr/config.h>
#include <vdr/tools.h>
#include <vdr/submenupatch.h>
#include <vector>
#include "version.h"
#include "menuorg.h"
#include "i18n.h"
#include <string>

using namespace std;
using namespace SubMenuPatch;

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
    if (!_subMenuProvider)
    {
        return tr("Failed to load config file");
    }
    else
    {
        return NULL;
    }
}

const char *MenuOrgPlugin::CommandLineHelp(void)
{
    // Return a string that describes all known command line options.
    return NULL;
}

bool MenuOrgPlugin::ProcessArgs(int argc, char *argv[])
{
    // Implement command line argument processing here if applicable.
    return true;
}

bool MenuOrgPlugin::Initialize(void)
{
    XmlMenu xmlMenu;

    string configFile = (string) ConfigDirectory() + "/menuorg.xml";

    MenuNode* menu = xmlMenu.LoadXmlMenu(configFile);
    if (menu)
    {
        _subMenuProvider = new SubMenuProvider(menu);
    }
    else
    {
        _subMenuProvider = NULL;
    }

    RegisterI18n(Phrases);

    return true;
}

bool MenuOrgPlugin::Start(void)
{
    // Start any background activities the plugin shall perform.
    return true;
}

void MenuOrgPlugin::Stop(void)
{
    // Stop any background activities the plugin shall perform.
}

void MenuOrgPlugin::Housekeeping(void)
{
    // Perform any cleanup or other regular tasks.
}

void MenuOrgPlugin::MainThreadHook(void)
{
    // Perform actions in the context of the main program thread.
    // WARNING: Use with great care - see PLUGINS.html!
}

cString MenuOrgPlugin::Active(void)
{
    // Return a message string if shutdown should be postponed
    return NULL;
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
    if (strcmp(Id, "SubMenuPatch-v0.1::SubMenuProvider") == 0 && _subMenuProvider) 
    {
        ISubMenuProvider** ptr = (ISubMenuProvider**)Data;
        *ptr = _subMenuProvider;

        return true;
    }

    return false;
}

const char **MenuOrgPlugin::SVDRPHelpPages(void)
{
    // Return help text for SVDRP commands this plugin implements
    return NULL;
}

cString MenuOrgPlugin::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
    // Process SVDRP commands this plugin implements
    return NULL;
}
