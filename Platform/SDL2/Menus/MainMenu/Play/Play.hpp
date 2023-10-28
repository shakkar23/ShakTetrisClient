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


class PlayMenuGUI : public GUI {


public:
	PlayMenuGUI();
	~PlayMenuGUI();
	TTF_Font* font{};
	Shakkar::Tetris* plugin;
	void init(RenderWindow& window) override;
	GUI_payload update(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) override;
	void render(RenderWindow& window) override;
	Sprite backGround;
	int selectedGame = 0;

private:
	bool pluginReInit = false;

public:
	int das = 0;
	int arr = 0;
};
#endif