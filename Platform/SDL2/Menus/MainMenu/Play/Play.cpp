#include "Play.hpp"
PlayMenuGUI::PlayMenuGUI(menuGUI* parentMenu) :
	subMenu(nullptr) {
	isInitialized = false;
	this->metaMenu = parentMenu;
}
PlayMenuGUI::PlayMenuGUI(RenderWindow& window, Shakkar::Tetris* game) :
	subMenu(nullptr) {
	isInitialized = false;
	Init(window);
}
PlayMenuGUI::~PlayMenuGUI() {
	if (subMenu != nullptr) {
		delete subMenu;
	}
}
void PlayMenuGUI::Init(RenderWindow& window) {
	if (!isInitialized) {
		background.Init("Asset/Sprites/invertedshak.png", window);
		PlayButton.Init("Asset/Sprites/MainMenu/PlayText.png", window);
		playButton.Init("Asset/Sprites/MainMenu/playText.png", window);
		exitButton.Init("Asset/Sprites/MainMenu/exitText.png", window);

		//change this
		background.sprite = { 0,0,DEFAULT_SCREEN_HEIGHT,DEFAULT_SCREEN_WIDTH };
		//background.textureRegion;

		playButton.sprite = { 0,0,177,61 };
		//playButton.textureRegion;

		PlayButton.sprite = { 0,61,370,63 };
		//PlayButton.textureRegion;

		exitButton.sprite = { 0,(61 + 63),160,61 };
		//exitButton.textureRegion;
		texs = { &background, &playButton, &PlayButton, &exitButton };
		highlighted = 0;
		isInitialized = true;
	}
	return;
}

void PlayMenuGUI::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
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
			case PlayMenuGUI::Play:

				break;
			case PlayMenuGUI::Settings:
				subMenu = new mainMenuGUI(this);

				break;
			case PlayMenuGUI::Exit:
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

void PlayMenuGUI::render(RenderWindow& window) {
	if (this->subMenu == nullptr) {
		Uint8 r = 0, g = 0, b = 255;
		Uint8 rDud = 255, gDud = 255, bDud = 255;
		switch ((GameState)highlighted)
		{
		case PlayMenuGUI::Play:
			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->getTex()),
				r, g, b);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->getTex()),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->getTex()),
				rDud, gDud, bDud);

			break;
		case PlayMenuGUI::Settings:

			SDL_SetTextureColorMod(&(*this->texs[(Play + 1)]->getTex()),
				rDud, gDud, bDud);
			SDL_SetTextureColorMod(&(*this->texs[(Settings + 1)]->getTex()),
				r, g, b);
			SDL_SetTextureColorMod(&(*this->texs[(Exit + 1)]->getTex()),
				rDud, gDud, bDud);
			break;
		case PlayMenuGUI::Exit:

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
	else if (!subMenu->isInitialized) {
		subMenu->Init(window);
		subMenu->render(window);
	}
	else {
		subMenu->render(window);
	}
}