#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../../../../ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"
#include "../../../../../ShakTris/Plugins/PluginHeaders/Tetris.hpp"
#include "../../../../../ShakTris/Input/Input.hpp"
#include "../../../headers/TextureManager.hpp"
#include "../../../headers/Engine.hpp"
#include "../../Menus.hpp"
#include "../MainMenu.hpp"


class PlayMenuGUI : public GUI {
public:
	PlayMenuGUI();
	~PlayMenuGUI();
	TTF_Font* font{};
	Shakkar::Tetris* plugin;
	void init(RenderWindow& window) override;
	GUI_payload update(const Shakkar::inputs& input) override;
	void render(RenderWindow& window) override;
	Sprite backGround;
	int selectedGame = 0;

private:
	bool pluginReInit = false;

public:
	int das = 0;
	int arr = 0;
};
