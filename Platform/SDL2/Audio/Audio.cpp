#include "Audio.hpp"

#include <vector>
#include <string>
#include <stdexcept>
#include <stdint.h>

#include <SDL.h>

namespace Shakkar {
    class Audio
    {
    public:
        Uint32 wav_length; // length of our sample
        Uint8* wav_buffer; // buffer containing our audio file
        SDL_AudioSpec wav_spec; // the specs of our piece of music
        Uint8* audio_pos; // global pointer to the audio buffer to be played
        Uint32 audio_len; // remaining length of the sample we have to play
        Uint8 volume;
        Audio(Uint8 volume) :volume(volume) {};
        ~Audio() {
            SDL_FreeWAV(wav_buffer);
        }

        // move
        Audio(Audio&& other) noexcept {
            wav_length = other.wav_length;
            wav_buffer = other.wav_buffer;
            wav_spec = other.wav_spec;
            audio_pos = other.audio_pos;
            audio_len = other.audio_len;
            volume = other.volume;
            other.wav_length = 0;
            other.wav_buffer = nullptr;
            other.audio_pos = nullptr;
            other.audio_len = 0;
        }
        // copy
        Audio(const Audio& other) = delete;
        // copy assignment
        Audio& operator=(const Audio& other) = delete;
        // move assignment
        Audio& operator=(Audio&& other) = delete;


    private:

    };
    std::vector<Shakkar::Audio> audios;
	


    void playAudio(std::string filepath, uint8_t volume) {
        Audio audio(volume);
        if (SDL_LoadWAV(filepath.c_str(), &audio.wav_spec, &audio.wav_buffer, &audio.wav_length) == NULL) {
            throw std::runtime_error("couldnt load music");
        }
        audio.audio_pos = audio.wav_buffer; // copy sound buffer
        audio.audio_len = audio.wav_length; // copy file length
        audios.emplace_back(std::move(audio));

    }




    class AudioManager
    {
    private:
        //wont be played although still needs to exist
        const char* mus2 = "Asset/Sounds/Sound.wav";

        static Uint32 wav_length; // length of our sample
        static Uint8* wav_buffer; // buffer containing our audio file

        static SDL_AudioSpec wav_spec; // the specs of our piece of music
    public:
        AudioManager();
        ~AudioManager();
    private:

        // audio callback function
        // here you have to copy the data of your audio buffer into the
        // requesting audio buffer (stream)
        // you should only copy as much as the requested length (len)
        static void callback(void* userdata, Uint8* stream, int len);

    };


    Uint32 AudioManager::wav_length = {}; // length of our sample
    Uint8* AudioManager::wav_buffer = {}; // buffer containing our audio file

    SDL_AudioSpec AudioManager::wav_spec = {}; // the specs of our piece of music

    AudioManager::~AudioManager() {
        SDL_FreeWAV(wav_buffer);
    }

    AudioManager::AudioManager() {
        // make a wav file to be called forever, imm abusing the forever part for cool things and such
        // notice that im not actually playing it, its just for the side affect of being called forever
        if (SDL_LoadWAV(mus2, &wav_spec, &wav_buffer, &wav_length) == NULL) {
            printf("couldnt load music");
        }

        wav_spec.callback = callback;

        /* Open the audio device */
        SDL_OpenAudio(&wav_spec, NULL);

        /* Start playing */
        SDL_PauseAudio(0);
    }

    void AudioManager::callback(void* userdata, Uint8* stream, int len) {
        //old code i want to keep
        // // simply copy from one buffer into the other
        //SDL_memcpy (stream, audio_pos, len); 		
        //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME / 8);// mix from one buffer into another

        const int length = len;

        //empty the stream, as it is not done by default :(
        //128 is actual silence
        SDL_memset(stream, 128, length);
        for (int i = 0; i < audios.size();) {
            auto &audio = audios[i];
            if (audio.audio_len == 0 || audio.audio_len == 1)
            {
                // turn index into iterator
                auto iter = audios.begin() + i;
                audios.erase(iter);
        }
            else {
                const int bounds = length > audio.audio_len ? audio.audio_len - 1 : length;
                //SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
                SDL_MixAudio(stream, audio.audio_pos, bounds, audio.volume);// mix from one buffer into another

                audio.audio_pos += bounds;
                audio.audio_len -= bounds;

                ++i;
            }
        }

    }

}