#pragma once
#ifndef SHAK_MAIN_MENU
#define SHAK_MAIN_MENU

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/Menus/MainMenu/Settings/Settings.hpp"
#include"Platform/SDL2/Menus/MainMenu/Play/Play.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/entity.hpp"

class menuGUI;

class mainMenuGUI : public GUI
{
public:
	mainMenuGUI();
	~mainMenuGUI() = default;

	Sprite background; 
	SurfaceTexture playButton;
	SurfaceTexture settingsButton; 
	SurfaceTexture exitButton;

	void init(RenderWindow &window) override;
	GUI_payload update(const Shakkar::inputs &input) override;
	void render(RenderWindow &window) override;
	
private:
	uint_fast8_t highlighted{};
	bool isEntered = false;
	enum GameState {
		Play,
		Settings,
		Exit,
		numberOfOptions
	};
	std::vector<SurfaceTexture*> texs;
};


#endif