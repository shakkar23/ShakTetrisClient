#pragma once
#include <vector>
#include <SDL.h>
namespace Shakkar {

    class autoAudio
    {
    public:
        Uint32 wav_length; // length of our sample
        Uint8* wav_buffer; // buffer containing our audio file
        SDL_AudioSpec wav_spec; // the specs of our piece of music
        Uint8* audio_pos; // global pointer to the audio buffer to be played
        Uint32 audio_len; // remaining length of the sample we have to play
        Uint8 volume;
        autoAudio(const char* file, Uint8 volume);
        ~autoAudio();

        static std::vector<autoAudio*> audios;
    private:
    };
};