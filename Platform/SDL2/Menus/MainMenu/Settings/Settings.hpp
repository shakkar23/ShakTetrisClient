#pragma once
#ifndef SHAK_SETTINGS
#define SHAK_SETTINGS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Platform/SDL2/headers/entity.hpp"
#include "Platform/SDL2/Menus/Menus.hpp"
#include "Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
#include "ShakTris/Input/Input.hpp"
#include "Platform/SDL2/headers/Engine.hpp"



class settingsMenuGUI : public GUI {


public:
	settingsMenuGUI() = default;
	~settingsMenuGUI() = default;

	SurfaceTexture background;
	SurfaceTexture playButton;
	SurfaceTexture settingsButton;
	SurfaceTexture exitButton;

	void init(RenderWindow& window) override;
	GUI_payload update(const Shakkar::inputs& input) override;
	void render(RenderWindow& window) override;
	
private:
	std::vector<SurfaceTexture*>texs;

	const int numberOfOptions = 3;
	uint_fast8_t highlighted{};
	bool isEntered = false;

	enum GameState {
		Play,
		Settings,
		Exit
	};

};

#endif