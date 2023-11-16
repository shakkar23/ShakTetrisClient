#include "MainMenu.hpp"

mainMenuGUI::mainMenuGUI()
{
	//change this
	background.destRect.w = DEFAULT_SCREEN_WIDTH;
	background.destRect.h = DEFAULT_SCREEN_HEIGHT;
	//background.textureRegion;

	playButton.destRect.w = 177;
	playButton.destRect.h = 61;
	//playButton.textureRegion;

	settingsButton.destRect.w = 370;
	settingsButton.destRect.h = 63;// x = 61
	settingsButton.destRect.y = playButton.destRect.h;
	//settingsButton.textureRegion;

	exitButton.destRect.w = 160;// x(61+63),160,61};
	exitButton.destRect.h = 61;
	exitButton.destRect.y = settingsButton.destRect.h + settingsButton.destRect.y;

	//exitButton.textureRegion;
	texs = { &playButton, &settingsButton, &exitButton };
}

void mainMenuGUI::init(RenderWindow& window) {
	background.load(window, "Asset/Sprites/MainMenu/background.png");
	settingsButton.load(window, "Asset/Sprites/MainMenu/settingsText.png");
	playButton.load(window, "Asset/Sprites/MainMenu/playText.png");
	exitButton.load(window, "Asset/Sprites/MainMenu/exitText.png");

	//change this
	background.destRect.w = DEFAULT_SCREEN_WIDTH;
	background.destRect.h = DEFAULT_SCREEN_HEIGHT;
	//background.textureRegion;

	playButton.destRect.w = 177;
	playButton.destRect.h = 61;
	//playButton.textureRegion;

	settingsButton.destRect.w = 370;
	settingsButton.destRect.h = 63;//x = 61
	settingsButton.destRect.y = playButton.destRect.h;
	//settingsButton.textureRegion;

	exitButton.destRect.w = 160;//x(61+63),160,61};
	exitButton.destRect.h = 61;
	exitButton.destRect.y = settingsButton.destRect.h + settingsButton.destRect.y;

	//exitButton.textureRegion;
	texs = { &playButton, &settingsButton, &exitButton };
	highlighted = 0;
	isInitialized = true;
};


GUI_payload mainMenuGUI::update(const Shakkar::inputs& input) {
	// in this scenario the top option is 0, and you increment to go down

	Shakkar::Key menuDown = input.getKey(SDLK_DOWN);
	Shakkar::Key menuUp = input.getKey(SDLK_UP);
	Shakkar::Key menuSelect = input.getKey(SDLK_RETURN);
	Shakkar::Key menuExit = input.getKey(SDLK_ESCAPE);

	if (menuDown.pressed) {
		highlighted = (highlighted + 1) % numberOfOptions;
	}
	if (menuUp.pressed) { //prevent menu underflow
		if (highlighted == 0) {
			highlighted = numberOfOptions;
		}
		highlighted = (highlighted - 1) % numberOfOptions;
	}
	if (menuSelect.pressed) {
		switch ((GameState)highlighted)
		{
		case mainMenuGUI::Play:

			return { new PlayMenuGUI(), true };
			break;
		case mainMenuGUI::Settings:
			return{ new settingsMenuGUI(), true };
			break;
		case mainMenuGUI::Exit:
			return { nullptr, false };
			break;
		default:
			break;
		}
	}
	return { nullptr, true };
}

void mainMenuGUI::render(RenderWindow& window) {

	Uint8 r = 0, g = 0, b = 255;
	Uint8 rDud = 255, gDud = 255, bDud = 255;
	switch ((GameState)highlighted)
	{
	case mainMenuGUI::Play:
		this->texs[Play]->setSurfaceColorMod(window,
			r, g, b);
		this->texs[Settings]->setSurfaceColorMod(window,
			rDud, gDud, bDud);
		this->texs[Exit]->setSurfaceColorMod(window,
			rDud, gDud, bDud);

		break;
	case mainMenuGUI::Settings:
		this->texs[Play]->setSurfaceColorMod(window,
			rDud, gDud, bDud);
		this->texs[Settings]->setSurfaceColorMod(window,
			r, g, b);
		this->texs[Exit]->setSurfaceColorMod(window,
			rDud, gDud, bDud);
		break;
	case mainMenuGUI::Exit:

		this->texs[Play]->setSurfaceColorMod(window,
			rDud, gDud, bDud);
		this->texs[Settings]->setSurfaceColorMod(window,
			rDud, gDud, bDud);
		this->texs[Exit]->setSurfaceColorMod(window,
			r, g, b);
		break;
	default:
		break;
	}
	window.clear();
	background.render(window);
	for (auto* e : texs)
		e->render(window);
}