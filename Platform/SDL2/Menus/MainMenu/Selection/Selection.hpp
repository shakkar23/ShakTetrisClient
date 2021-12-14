#pragma once
#ifndef SHAK_SELECT
#define SHAK_SELECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/Game.hpp"
#include "ShakTris/Plugins/PluginHeaders/Tetris.hpp"
#include "ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"


class SelectionGUI : public menuGUI {


public:
	SelectionGUI() = delete;
	SelectionGUI(menuGUI* parentMenu);

	menuGUI* metaMenu;
	Shakkar::Tetris* plugin;
	~SelectionGUI();

	void Init(RenderWindow& window);
	void menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow& window);

private:
	bool pluginReInit = false;
};
#endif