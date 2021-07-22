#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"Platform/SDL2/headers/entity.hpp"
#include"Platform/SDL2/headers/RenderWindow.hpp"

class gameManager
{
public:
	gameManager()
	{
		MainMenuIsInitialized = false;
		DefaultTetrisIsInitialized = false;
		SettingsIsInitialized = false;
		ExitIsInitialized = false;
	}
	bool MainMenuIsInitialized		: 1;
	bool DefaultTetrisIsInitialized : 1;
	bool SettingsIsInitialized		: 1;
	bool ExitIsInitialized			: 1;
	void gameLogic(RenderWindow window);

	~gameManager()
	{
	}

private:
	enum GameState
	{
		MainMenu,
		DefaultTetris,
		Settings,
		Exit
	};
	GameState GameState = MainMenu;
}GameManager;







