#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "Simple-INI-Parser/include/SimpleIniParser.hpp"
#include "ShakTris/Input/Input.hpp"
namespace Shakkar {
	namespace Keyboard {
		void pressKey(SDL_Scancode scan, Shakkar::inputBitmap &input);
		void unpressKey(SDL_Scancode scan, Shakkar::inputBitmap &input);
	}
}
