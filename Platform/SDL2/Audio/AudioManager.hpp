#include "Audio.hpp"

namespace Shakkar {
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
};
