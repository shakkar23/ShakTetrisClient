#pragma once
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "Platform/SDL2/headers/RenderWindow.hpp"

// this is the gameManager, it redirects the thread to wherever it needs to go
class gameManager : public menuGUI
{
public:
	menuGUI* mainMenu;
	void Init(RenderWindow& window);
	void menuGUI::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
	void render(RenderWindow &window);

	gameManager() : mainMenu(nullptr)
	{
		mainMenu = new mainMenuGUI;
		isInitialized = true;
	}
	~gameManager()
	{
		delete mainMenu;
		mainMenu = nullptr;
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
