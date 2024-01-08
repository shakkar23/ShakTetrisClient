#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "../../ShakTris/Input/Input.hpp"
#include "../gameManager/gameManager.hpp"
#include "../Menus/Menus.hpp"
#include "TextureManager.hpp"
#include "RenderWindow.hpp"

constexpr auto DEFAULT_SCREEN_WIDTH = 1920;
constexpr auto DEFAULT_SCREEN_HEIGHT = 1080;

constexpr auto UPDATES_A_SECOND = 100;
