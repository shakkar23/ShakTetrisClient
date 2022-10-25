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

	Sprite background; 
	SurfaceTexture playButton;
	SurfaceTexture settingsButton; 
	SurfaceTexture exitButton;
	menuGUI* metaMenu;
	menuGUI* subMenu;
	~mainMenuGUI();

	void Init(RenderWindow &window) override;
	void menuLogic(Shakkar::inputBitmap &input, Shakkar::inputBitmap& prevInput) override;
	void render(RenderWindow &window) override;
	
private:
	uint_fast8_t highlighted{};
	bool isEntered = false;
	enum GameState {
		Play,
		Settings,
		Exit,
		numberOfOptions
	};
};


#endif