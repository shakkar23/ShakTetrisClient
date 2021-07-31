#pragma once

#include<stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/headers/RenderWindow.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"


//default class for menus,  you will need this for making new sub menus in the game
class menuGUI
{
public:
	
	std::vector<autoTexture*> texs; // this should have what you want to display, the 0th index being the bottom most texture (background)

	virtual void Init(RenderWindow& window) = 0; // will be called to initialize the class, please set isInitialized as true when this is called
	virtual void menuLogic(Shakkar::inputBitmap input) = 0; // use the menu variables as the controls
	
	bool isInitialized = false;
private:

};


// this is the gameManager, it redirects the thread to wherever it needs to go
class gameManager : public menuGUI
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
	mainMenuGUI *mainMenu;
	void Init(RenderWindow& window);
	void menuGUI::menuLogic(Shakkar::inputBitmap input);

	~gameManager()
	{
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





