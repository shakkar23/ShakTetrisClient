#pragma once
#ifndef SHAK_MAIN_MENU
#define SHAK_MAIN_MENU

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/Menus/MainMenu/Settings/Settings.hpp"
#include"Platform/SDL2/Menus/MainMenu/Play/Play.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/entity.hpp"

class menuGUI;

class mainMenuGUI : public menuGUI
{
public:
	mainMenuGUI();
	mainMenuGUI(RenderWindow& window);
	mainMenuGUI(menuGUI* parentMenu);

	autoTexture background; 
	autoTexture playButton;
	autoTexture settingsButton; 
	autoTexture exitButton;
	menuGUI* metaMenu;
	menuGUI* subMenu;
	~mainMenuGUI();

	void Init(RenderWindow &window);
	void menuLogic(Shakkar::inputBitmap &input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow &window);
	
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


#endif