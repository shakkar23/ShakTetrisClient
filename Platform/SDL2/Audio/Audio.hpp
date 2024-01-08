#pragma once

#include <string>
#include <stdint.h>
#include <vector>
#include <SDL.h>

namespace Shakkar {
	void playAudio(std::string filepath, uint8_t volume);
	
	void playMusic(std::string filepath, uint8_t volume);
	void stopMusic();
};