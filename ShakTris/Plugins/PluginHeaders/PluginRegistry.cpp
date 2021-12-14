#include"PluginRegistry.hpp"

namespace Correct {
    std::vector<Shakkar::Tetris*> games;
};

std::vector<Shakkar::autoAudio*> Shakkar::autoAudio::audios;

void Shakkar::Plugins::add2(Shakkar::Tetris* game) {
    getEntries().emplace_back(game);
}

std::vector<Shakkar::Tetris*> &Shakkar::Plugins::getEntries() {
    return Correct::games;
}
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