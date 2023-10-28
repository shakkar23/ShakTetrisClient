#pragma once

#ifndef SHAK_GAME_MANAGER
#define SHAK_GAME_MANAGER

#include "Platform/SDL2/Menus/Menus.hpp" 
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp" 
#include "Platform/SDL2/headers/RenderWindow.hpp"
#include "ShakTris/Plugins/PluginManager.hpp"
#include <thread>


// this is the gameManager, it redirects the thread to wherever it needs to go
class gameManager
{
public:
	// void Init(RenderWindow& window) override;
	bool update(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow &window);

	gameManager(RenderWindow& window) { 
		PluginManager::loadPlugins(window);
		subGUIs.push_back(new mainMenuGUI());
	}
	~gameManager()
	{
		unloadPlugins();
	}
private:
	enum class GameState : uint_fast8_t
	{
		MainMenu,
		DefaultTetris,
		Settings,
		Exit
	};
	GameState GameState = gameManager::GameState::MainMenu;
	std::vector<GUI*> subGUIs;
};

#endif