#pragma once
#ifndef SHAK_MENUS
#define SHAK_MENUS

#include<stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/headers/RenderWindow.hpp"
#include "ShakTris/Input/Input.hpp"

#include <utility>

class GUI;
typedef std::pair<GUI*, bool> GUI_payload;
//default class for menus,  you will need this for making new sub menus in the game
class GUI
{
public:
	virtual void init(RenderWindow& window) = 0; // will be called to initialize the class, please set isInitialized as true when this is called
	virtual GUI_payload update(Shakkar::inputBitmap &input, Shakkar::inputBitmap& prevInput) = 0; // use the menu variables as the controls
	virtual void render(RenderWindow& window) = 0;
	bool isInitialized = false;
private:

};

// GUI * is a pointer to the GUI class you just made
// bool is whether or not the current menu should be deleted

#endif