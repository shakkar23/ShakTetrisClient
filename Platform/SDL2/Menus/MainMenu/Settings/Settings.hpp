#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"


class settingsMenuGUI : public menuGUI {


public:
	settingsMenuGUI() :
		submenu(nullptr), isInitialized(false)
	{}
	settingsMenuGUI(RenderWindow& window) :
		submenu(nullptr) {
		Init(window);
	}
	autoTexture background;
	autoTexture playButton;
	autoTexture settingsButton;
	autoTexture exitButton;
	menuGUI* submenu;
	~settingsMenuGUI()
	{
	}

	void Init(RenderWindow& window);
	void menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow& window);
	bool isInitialized = false;
private:
	uint_fast8_t highlighted{};
	const int numberOfOptions = 3;
	bool isEntered = false;
	enum GameState {
		Play,
		Settings,
		Exit
	};

};