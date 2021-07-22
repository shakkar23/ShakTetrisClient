#include "MainMenu.hpp"

void mainMenuGUI::Init(RenderWindow window) {
	if (!isInitialized) {
		invertedShak.Init(0, 0, "Asset/Sprites/invertedshak.png", 480, 360, window);
		blankMenu.Init(0, 0, "Asset/Sprites/blankmenu.png", 480, 360, window);
		highlightedMenu.Init(0, 0, "Asset/Sprites/highlightedmenu.png", 480, 360, window);
	}
	return;
}

