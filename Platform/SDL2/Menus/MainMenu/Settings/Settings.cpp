#include "Settings.hpp"

//UHHHHHHHHHHHHHHHHHHHHHHHHHH

//settingsMenuGUI::settingsMenuGUI() :
//	subMenu(nullptr) {
//	isInitialized = false;
//}
settingsMenuGUI::settingsMenuGUI(menuGUI *parentMenu) :
	subMenu(nullptr) {
	isInitialized = false;
	this->metaMenu = parentMenu;
}
settingsMenuGUI::settingsMenuGUI(RenderWindow& window) :
	subMenu(nullptr) {
	isInitialized = false;
	Init(window);
}
settingsMenuGUI::~settingsMenuGUI() {
	if (subMenu != nullptr) {
		delete subMenu;
	}
}
void settingsMenuGUI::Init(RenderWindow& window) {
	if (!isInitialized) {
		background.load(window, "Asset/Sprites/invertedshak.png");
		settingsButton.load(window, "Asset/Sprites/MainMenu/settingsText.png");
		playButton.load (window, "Asset/Sprites/MainMenu/playText.png");
		exitButton.load(window, "Asset/Sprites/MainMenu/exitText.png");

		//change this
		background.destRect = { 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT };
		//background.textureRegion;

		playButton.destRect = { 0,0,177,61 };
		//playButton.textureRegion;

		settingsButton.destRect = { 0,61,370,63 };
		//settingsButton.textureRegion;

		exitButton.destRect = { 0,(61 + 63),160,61 };
		//exitButton.textureRegion;
		texs = { &background, &playButton, &settingsButton, &exitButton };
		highlighted = 0;
		isInitialized = true;
	}
	return;
}

void settingsMenuGUI::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
	// in this scenario the top option is 0, and you increment to go down

	if (submenuWasDeleted) {
		subMenu = nullptr;
		submenuWasDeleted = false;
	}
	if (this->subMenu == nullptr) {
		if (input.menuDown && !prevInput.menuDown) {
			highlighted = (highlighted + 1) % numberOfOptions;
		}
		if (input.menuUp && !prevInput.menuUp) { //prevent menu underflow
			if (highlighted == 0) {
				highlighted = numberOfOptions;
			}
			highlighted = (highlighted - 1) % numberOfOptions;
		}
		if (input.menuSelect && !prevInput.menuSelect) {
			switch ((GameState)highlighted)
			{
			case settingsMenuGUI::Play:
				subMenu = new PlayMenuGUI(this);
				break;
			case settingsMenuGUI::Settings:
				subMenu = new mainMenuGUI(this);
				
				break;
			case settingsMenuGUI::Exit:
				metaMenu->submenuWasDeleted = true;
				delete this;
				break;
			default:
				break;
			}
		}
	}
	else { subMenu->menuLogic(input, prevInput); }
}

void settingsMenuGUI::render(RenderWindow& window) {
	if (this->subMenu == nullptr) {
		Uint8 r = 0, g = 0, b = 255;
		Uint8 rDud = 255, gDud = 255, bDud = 255;
		switch ((GameState)highlighted)
		{
		case settingsMenuGUI::Play:
			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->texture),
				r, g, b);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->texture),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->texture),
				rDud, gDud, bDud);

			break;
		case settingsMenuGUI::Settings:

			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->texture),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->texture),
				r, g, b);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->texture),
				rDud, gDud, bDud);
			break;
		case settingsMenuGUI::Exit:

			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->texture),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->texture),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->texture),
				r, g, b);
			break;
		default:
			break;
		}
		for (auto* e : texs) {
			e->render(window);
		}
	}
	else if (!subMenu->isInitialized) {
		subMenu->Init(window);
		subMenu->render(window);
	}
	else {
		subMenu->render(window);
	}
}