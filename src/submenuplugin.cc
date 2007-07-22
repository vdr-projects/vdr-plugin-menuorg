/*
 * submenu.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include <vdr/plugin.h>
#include <vdr/config.h>
#include <vdr/tools.h>
#include <vdr/submenupatch.h>
#include <vector>
#include "version.h"
#include "submenuplugin.h"

using namespace SubMenuPatch;

SubMenuPlugin::SubMenuPlugin(void)
{
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}


SubMenuPlugin::~SubMenuPlugin()
{
  // Clean up after yourself!
}

const char* SubMenuPlugin::Version(void)
{
    return VERSION;
}

const char* SubMenuPlugin::Description(void)
{
    return tr("TODO: Insert Description");
}

const char* SubMenuPlugin::MainMenuEntry(void)
{
    return tr("TODO: MainMenuEntry");
}
  
const char *SubMenuPlugin::CommandLineHelp(void)
{
    // Return a string that describes all known command line options.
    return NULL;
}

bool SubMenuPlugin::ProcessArgs(int argc, char *argv[])
{
    // Implement command line argument processing here if applicable.
    return true;
}

bool SubMenuPlugin::Initialize(void)
{
    // Initialize any background activities the plugin shall perform.
    return true;
}

bool SubMenuPlugin::Start(void)
{
    // Start any background activities the plugin shall perform.
    return true;
}

void SubMenuPlugin::Stop(void)
{
    // Stop any background activities the plugin shall perform.
}

void SubMenuPlugin::Housekeeping(void)
{
    // Perform any cleanup or other regular tasks.
}

void SubMenuPlugin::MainThreadHook(void)
{
    // Perform actions in the context of the main program thread.
    // WARNING: Use with great care - see PLUGINS.html!
}

cString SubMenuPlugin::Active(void)
{
    // Return a message string if shutdown should be postponed
    return NULL;
}

cOsdObject *SubMenuPlugin::MainMenuAction(void)
{
    // Perform the action when selected from the main VDR menu.
    return NULL;
}

cMenuSetupPage *SubMenuPlugin::SetupMenu(void)
{
    // Return a setup menu in case the plugin supports one.
    return NULL;
}

bool SubMenuPlugin::SetupParse(const char *Name, const char *Value)
{
    // Parse your own setup parameters and store their values.
    return false;
}

bool SubMenuPlugin::Service(const char *Id, void *Data)
{
    if (strcmp(Id, "SubMenuPatch-v0.1::SubMenuProvider") == 0) 
    {
        ISubMenuProvider** ptr = (ISubMenuProvider**)Data;
        *ptr = &_subMenuProvider;

        return true;
    }

    return false;
}

const char **SubMenuPlugin::SVDRPHelpPages(void)
{
    // Return help text for SVDRP commands this plugin implements
    return NULL;
}

cString SubMenuPlugin::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
    // Process SVDRP commands this plugin implements
    return NULL;
}
