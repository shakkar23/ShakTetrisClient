#pragma once
#ifndef SHAK_PLAY
#define SHAK_PLAY
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/Engine.hpp"
#include "ShakTris/Plugins/PluginHeaders/Tetris.hpp"
#include "ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"


class PlayMenuGUI : public menuGUI {


public:
	PlayMenuGUI() = delete;
	PlayMenuGUI(menuGUI* parentMenu);
	~PlayMenuGUI();
	TTF_Font* font{};
	menuGUI* metaMenu;
	Shakkar::Tetris* plugin;
	void Init(RenderWindow& window);
	void menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow& window);
	Sprite backGround;
	int selectedGame = 0;

private:
	bool pluginReInit = false;


public:
	int das = 0;
	int arr = 0;
};
#endif