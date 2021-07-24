#include "MainMenu.hpp"

void mainMenuGUI::Init(RenderWindow window) {
	if (!isInitialized) {
		invertedShak.Init("Asset/Sprites/invertedshak.png", window);
		blankMenu.Init("Asset/Sprites/blankmenu.png", window);
		highlightedMenu.Init("Asset/Sprites/highlightedmenu.png", window);
	}
	return;
}

