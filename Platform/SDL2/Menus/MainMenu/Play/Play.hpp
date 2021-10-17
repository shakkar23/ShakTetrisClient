#pragma once
#ifndef SHAK_PLAY
#define SHAK_PLAY
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/Game.hpp"
#include "ShakTris/Plugins/PluginHeaders/Tetris.hpp"


class PlayMenuGUI : public menuGUI {


public:
	PlayMenuGUI() = delete;
	PlayMenuGUI(RenderWindow& window, Shakkar::Tetris *game);
	PlayMenuGUI(menuGUI* parentMenu);

	autoTexture background;
	autoTexture playButton;
	autoTexture PlayButton;
	autoTexture exitButton;
	menuGUI* metaMenu;
	menuGUI* subMenu;
	~PlayMenuGUI();

	void Init(RenderWindow& window);
	void menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow& window);

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