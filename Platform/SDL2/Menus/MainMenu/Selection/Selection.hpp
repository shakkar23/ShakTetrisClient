#pragma once
#ifndef SHAK_SELECT
#define SHAK_SELECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/Engine.hpp"
#include "ShakTris/Plugins/PluginHeaders/Tetris.hpp"
#include "ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"


class SelectionGUI : public GUI {


public:
	SelectionGUI();

	Shakkar::Tetris* plugin;
	~SelectionGUI();

	void init(RenderWindow& window) override;
	GUI_payload update(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) override;
	void render(RenderWindow& window) override;

private:
	bool pluginReInit = false;
};
#endif