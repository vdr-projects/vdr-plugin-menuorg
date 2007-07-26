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
const unsigned int ENTER = 0;
const unsigned int LEAVE = 1;

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
		int _MenuZuordnung[5][20][2];     // Speichert die Zuodnung
						  // erster Wert MenuIndex | zweiter Wert MenuItemIndex | dritter wert 0=Enter, 1=Leave

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
