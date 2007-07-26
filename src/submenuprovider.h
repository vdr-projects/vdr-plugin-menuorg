#ifndef ___SUBMENUPROVIDER_H
#define ___SUBMENUPROVIDER_H

#include <vdr/submenupatch.h>

using namespace SubMenuPatch;

/*
struct sSubMenu
{
	int MainMenuIndex;
	int NextMenuIndex;
};
*/

class SubMenuProvider: public ISubMenuProvider
{
	private:
		MainMenuItemsList _osdItems;      // Enthält das aktuelle MenüItem (kann weg)
		MainMenuItemsList _myOsdItems[5]; // Enthält alle verfügbaren Menüs
		bool _OsdSet;                     // Zum entscheiden, ob in MainMenuItems() die Testmenus erstellt werden müssen 
						  // Später evtl. an diesem Punkt die XML Datei laden
		bool _inSubMenu;
		int _MenuIndex;                   // Der Index des aktuellen Menüs
		int _nextMenuIndex;               // Enthält den Index des nächsten Menüs
		int _MenuZuordnung[5][20];        // Speichert die Zuodnung

	public:
		SubMenuProvider();
		virtual MainMenuItemsList* MainMenuItems();
		virtual void EnterSubMenu(cOsdItem* item);
		virtual bool LeaveSubMenu();

	private:
		void ResetMainMenuItemsList();
		void CreateTestMenus();
};

#endif
