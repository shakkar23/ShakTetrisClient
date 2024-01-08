#include "Audio.hpp"

#include <vector>
#include <string>
#include <stdexcept>
#include <stdint.h>

#include <SDL.h>
#include <SDL_mixer.h>

namespace Shakkar {
    static Mix_Music* cur_music = nullptr;

    void playAudio(std::string filepath, uint8_t volume) {
        Mix_Chunk * chunk = Mix_LoadWAV(filepath.c_str());
        if (chunk == nullptr) {
			throw std::runtime_error("couldnt load chunk");
		}
        Mix_PlayChannel(-1, chunk, 0);
        Mix_VolumeChunk(chunk, volume);
    }

    void playMusic(std::string filepath, uint8_t volume) {
		Mix_Music * music = Mix_LoadMUS(filepath.c_str());
		if (music == nullptr) {
        	throw std::runtime_error("couldnt load music");
        }

        if (cur_music) {
            Mix_HaltMusic();
            Mix_FreeMusic(cur_music);
        }

        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(volume);
        
        cur_music = music;
    }

    void stopMusic() {
        if (cur_music) {
			Mix_HaltMusic();
			Mix_FreeMusic(cur_music);
			cur_music = nullptr;
		}
    }
}