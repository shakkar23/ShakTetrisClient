#include "MainMenu.hpp"

void mainMenuGUI::Init(RenderWindow& window) {
	if (!isInitialized) {
		invertedShak.Init("Asset/Sprites/invertedshak.png", window);
		blankMenu.Init("Asset/Sprites/blankmenu.png", window);
		highlightedMenu.Init("Asset/Sprites/highlightedmenu.png", window);

		
		invertedShak.sprite = { 0,0,1905,1080 };
		invertedShak.textureRegion = { 0,0,480,360 };

		blankMenu.sprite = { 0,0,112,30 };
		blankMenu.textureRegion = { 0,0,112,30 };

		highlightedMenu.sprite = { 0,30,112 * 2,30 * 2 };
		highlightedMenu.textureRegion = { 0,0,112,30 };

	}
	return;
}

void mainMenuGUI::menuLogic(Shakkar::inputBitmap input) {
	 // in this scenario the top option is 0, and you increment to go down
	if (Shakkar::input.menuDown) {
		selected++;
		if (selected > numberOfOptions) {
			selected = 0;
		}
	};
	if (Shakkar::input.menuUp) { 
		if (selected == 0) { 
			selected = numberOfOptions; 
		} 
		selected--; 
	}
}

