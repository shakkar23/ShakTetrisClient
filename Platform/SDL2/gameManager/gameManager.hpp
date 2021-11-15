#pragma once

#ifndef SHAK_GAME_MANAGER
#define SHAK_GAME_MANAGER

#include "Platform/SDL2/Menus/Menus.hpp" 
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp" 
#include "Platform/SDL2/headers/RenderWindow.hpp"
#include "ShakTris/Plugins/PluginManager.hpp"
#include <thread>


// this is the gameManager, it redirects the thread to wherever it needs to go
class gameManager : public menuGUI
{
public:
	menuGUI* mainMenu;
	void Init(RenderWindow& window) override;
	void menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) override;
	bool gameLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow &window) override;

	gameManager()
	{
		mainMenu = new mainMenuGUI(this);
		isInitialized = true;
		
	}
	~gameManager()
	{
		delete mainMenu;
		mainMenu = nullptr;
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
};
extern gameManager GameManager;

#endif