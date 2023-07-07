#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include "headers/entity.hpp"
#include "headers/RenderWindow.hpp"
#include "Keyboard/Keyboard.hpp"
#include "gameManager/gameManager.hpp"
#include "Menus/Menus.hpp"
#include "../../ShakTris/Plugins/PluginManager.hpp"

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		std::cout << "HEY.. Audio_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
		<< std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
		<< std::endl;
	if (TTF_Init() != 0)
		std::cout << "HEY.. ttf_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
		<< std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("Shaktris", 480 * 2, 272 * 2);
	GameManager.Init(window);
	AudioManager manager;
	Shakkar::inputBitmap input = Shakkar::inputBitmap();
	Shakkar::inputBitmap prevInput = Shakkar::inputBitmap();

	bool gameRunning = true;
	SDL_Event event;

	// rendering constantly, and not actually displaying causes memory to stack higher and higher until the frames can be shown
	bool shouldDisplay = false;
	bool windowSizedChanged = false;

	double alpha = 0.0;
	Uint64 last_time = SDL_GetPerformanceCounter();
	Uint64 ticks = 0;

	while (gameRunning) {

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
					shouldDisplay = false;
				}
				else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
					shouldDisplay = false;
				}
				else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					windowSizedChanged = true;
				}
			}
			else if ((event.key.type == SDL_KEYDOWN) || (event.key.type == SDL_KEYUP)) {
				if (event.key.state == SDL_PRESSED) {
					if (event.key.repeat)
						continue;
					Shakkar::Keyboard::pressKey(event.key.keysym.scancode, input);
					//std::cout << "Physical" << SDL_GetScancodeName(event.key.keysym.scancode) << " key acting as the " << SDL_GetKeyName(event.key.keysym.sym) << " key" << std::endl;
				}
				else {
					Shakkar::Keyboard::unpressKey(event.key.keysym.scancode, input);
				}
			}
			else if (event.type == SDL_QUIT)
				gameRunning = false;

		}

		// skip frames that cant be shown due to window not currently accepting frames to display
		if (!shouldDisplay) {

			const auto now = SDL_GetPerformanceCounter();
			alpha += (double)((double)(now - last_time) / SDL_GetPerformanceFrequency() * UPDATES_A_SECOND);
			last_time = now;

			while (alpha > 1.0) {
				if (!GameManager.gameLogic(input, prevInput)) {
					gameRunning = false;
					break;
				}
				prevInput = input;

				alpha -= 1.0;
			}
			if (gameRunning) {
				GameManager.render(window);
			}
			else {
				gameRunning = false;
			}


		}
	}

	window.cleanUp();
	SDL_Quit();
	TTF_Quit();
	return 0;
}
