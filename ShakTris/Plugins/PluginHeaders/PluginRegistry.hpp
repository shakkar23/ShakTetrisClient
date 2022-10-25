#pragma once
#include <vector>
#include "Tetris.hpp"
#include "../PluginManager.hpp"
#include <concepts>
#include <type_traits>

#define DLL extern "C" __declspec(dllexport)

#define PLUGIN_SETUP(name, author, description) PLUGIN_SETUP_IMPL(PLUGIN_NAME, name, author, description)

#define PLUGIN_SETUP_IMPL(namespaceName, name, author, description)                                \
    namespace namespaceName {                                                                       \
        DLL void initializePlugin(void *window);                                                     \
        DLL const char* getPluginName() { return name; }                                              \
        DLL const char* getPluginAuthor() { return author; }                                           \
        DLL const char* getPluginDescription() { return description; }                                  \
        }                                                                                                \
    void namespaceName::initializePlugin(void *window)

namespace Shakkar {
    using std::derived_from;
    //tamplate stuff to make sure they are definitely being derived from my base class

    
    struct Plugins {
        Plugins() = delete;
        template<Shakkar::derived_from<Shakkar::Tetris> T, typename ... Args>
        static void addorig(Args&& ... args) {
            return add2(new T(std::forward<Args>(args)...));
        }
        template<Shakkar::derived_from<Shakkar::Tetris> T>
            static void addnew() {
            return add2(new T());
        }

        static std::vector<Tetris*> &getEntries();

        static void add2(Tetris* game);


    };


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
