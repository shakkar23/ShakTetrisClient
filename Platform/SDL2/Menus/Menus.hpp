#pragma once

#include<stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/headers/RenderWindow.hpp"
#include "ShakTris/Input/Input.hpp"


//default class for menus,  you will need this for making new sub menus in the game
class menuGUI
{
public:
	
	std::vector<autoTexture*> texs; // this should have what you want to display, the 0th index being the bottom most texture (background)

	virtual void Init(RenderWindow& window) = 0; // will be called to initialize the class, please set isInitialized as true when this is called
	virtual void menuLogic(Shakkar::inputBitmap &input, Shakkar::inputBitmap& prevInput) = 0; // use the menu variables as the controls
	virtual void render(RenderWindow& window) = 0;
	bool isInitialized = false;
private:

};

