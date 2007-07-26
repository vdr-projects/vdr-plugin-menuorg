#ifndef ___MENUORGPLUGIN_H
#define ___MENUORGPLUGIN_H

#include <vdr/plugin.h>
//#include <vdr/config.h>
//#include <vdr/tools.h>
#include "submenuprovider.h"

using namespace SubMenuPatch;

class MenuOrgPlugin : public cPlugin
{
    private:
        SubMenuProvider _subMenuProvider;

    public:
        MenuOrgPlugin(void);
        virtual ~MenuOrgPlugin();
        virtual const char *Version(void);
        virtual const char *Description(void);
        virtual const char *CommandLineHelp(void);
        virtual bool ProcessArgs(int argc, char *argv[]);
        virtual bool Initialize(void);
        virtual bool Start(void);
        virtual void Stop(void);
        virtual void Housekeeping(void);
        virtual void MainThreadHook(void);
        virtual cString Active(void);
        virtual const char *MainMenuEntry(void);
        virtual cOsdObject *MainMenuAction(void);
        virtual cMenuSetupPage *SetupMenu(void);
        virtual bool SetupParse(const char *Name, const char *Value);
        virtual bool Service(const char *Id, void *Data = NULL);
        virtual const char **SVDRPHelpPages(void);
        virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
};
  
extern "C" void* VDRPluginCreator();

#endif