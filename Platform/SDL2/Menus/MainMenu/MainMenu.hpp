#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"Platform/SDL2/Menus/Menus.hpp"


class mainMenuGUI
{
public:
	mainMenuGUI()
	{
	}
	autoTexture invertedShak; 
	autoTexture blankMenu; 
	autoTexture highlightedMenu;

	~mainMenuGUI()
	{
	}

	void Init(RenderWindow window);

private:
	friend gameManager;
	bool isInitialized = false;
}mainMenuGUI;


