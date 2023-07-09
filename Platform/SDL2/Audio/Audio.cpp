#include "Audio.hpp"

std::vector<Shakkar::autoAudio*> Shakkar::autoAudio::audios;
namespace Shakkar {

	Shakkar::autoAudio::autoAudio(const char* file, Uint8 volume) : volume(volume) {
		if (SDL_LoadWAV(file, &wav_spec, &wav_buffer, &wav_length) == NULL) {
			printf("couldnt load music");
		}
		audio_pos = wav_buffer; // copy sound buffer
		audio_len = wav_length; // copy file length
		audios.emplace_back(this);
	}
	Shakkar::autoAudio::~autoAudio() {
		SDL_FreeWAV(wav_buffer);
	}
}
