#include "Settings.hpp"

//UHHHHHHHHHHHHHHHHHHHHHHHHHH


void settingsMenuGUI::Init(RenderWindow& window) {
	if (!isInitialized) {
		background.Init("Asset/Sprites/invertedshak.png", window);
		settingsButton.Init("Asset/Sprites/MainMenu/settingsText.png", window);
		playButton.Init("Asset/Sprites/MainMenu/playText.png", window);
		exitButton.Init("Asset/Sprites/MainMenu/exitText.png", window);

		//change this
		background.sprite = { 0,0,1920,1080 };
		//background.textureRegion;

		playButton.sprite = { 0,0,177,61 };
		//playButton.textureRegion;

		settingsButton.sprite = { 0,61,370,63 };
		//settingsButton.textureRegion;

		exitButton.sprite = { 0,(61 + 63),160,61 };
		//exitButton.textureRegion;
		texs = { &background, &playButton, &settingsButton, &exitButton };
		highlighted = 0;
		isInitialized = true;
	}
	return;
}

void settingsMenuGUI::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
	// in this scenario the top option is 0, and you increment to go down
	if (this->submenu == nullptr) {
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

				break;
			case settingsMenuGUI::Settings:
				submenu = new mainMenuGUI();
				break;
			case settingsMenuGUI::Exit:

				break;
			default:
				break;
			}
		}
	}
	else { submenu->menuLogic(input, prevInput); }
}

void settingsMenuGUI::render(RenderWindow& window) {
	if (this->submenu == nullptr) {
		Uint8 r = 0, g = 0, b = 255;
		Uint8 rDud = 255, gDud = 255, bDud = 255;
		switch ((GameState)highlighted)
		{
		case settingsMenuGUI::Play:
			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->getTex()),
				r, g, b);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->getTex()),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->getTex()),
				rDud, gDud, bDud);

			break;
		case settingsMenuGUI::Settings:

			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->getTex()),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->getTex()),
				r, g, b);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->getTex()),
				rDud, gDud, bDud);
			break;
		case settingsMenuGUI::Exit:

			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->getTex()),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->getTex()),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->getTex()),
				r, g, b);
			break;
		default:
			break;
		}
		for (autoTexture* e : texs) {
			window.render(*e);
		}
	}
	else if (!submenu->isInitialized) {
		submenu->Init(window);
		submenu->render(window);
	}
	else {
		submenu->render(window);
	}
}