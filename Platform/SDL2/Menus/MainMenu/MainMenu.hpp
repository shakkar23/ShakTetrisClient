#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/Settings/Settings.hpp"
#include "ShakTris/Input/Input.hpp"

class menuGUI;

class mainMenuGUI : public menuGUI
{
public:
	mainMenuGUI():
	submenu(nullptr), isInitialized(false) {
	}
	mainMenuGUI(RenderWindow& window) :
		submenu(nullptr) {
		Init(window);
	}
	autoTexture background; 
	autoTexture playButton;
	autoTexture settingsButton; 
	autoTexture exitButton;
	menuGUI* submenu;
	~mainMenuGUI()
	{}

	void Init(RenderWindow &window);
	void menuLogic(Shakkar::inputBitmap &input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow &window);
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


