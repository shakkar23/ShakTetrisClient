#pragma once
#ifndef SHAK_SETTINGS
#define SHAK_SETTINGS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/Game.hpp"



class settingsMenuGUI : public menuGUI {


public:
	settingsMenuGUI() = delete;
	settingsMenuGUI(RenderWindow& window);
	settingsMenuGUI(menuGUI * parentMenu);

	SurfaceTexture background;
	SurfaceTexture playButton;
	SurfaceTexture settingsButton;
	SurfaceTexture exitButton;
	menuGUI* metaMenu;
	menuGUI* subMenu;
	~settingsMenuGUI();

	void Init(RenderWindow& window);
	void menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow& window);
	
private:
	std::vector<SurfaceTexture*>texs;
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