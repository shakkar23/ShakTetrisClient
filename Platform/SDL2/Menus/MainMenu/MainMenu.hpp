#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"

#include <vector>

class mainMenuGUI : public menuGUI
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

	void menuGUI::Init(RenderWindow &window);
	void menuGUI::menuLogic(Shakkar::inputBitmap input);
	bool isInitialized = false;
private:
	uint_fast8_t selected{};
	const int numberOfOptions = 4;
};


