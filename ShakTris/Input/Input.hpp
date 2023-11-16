#pragma once
#ifndef SHAK_INPUT
#define SHAK_INPUT
#include <vector>
#include <SDL2/SDL.h>

namespace Shakkar {
    // taken inspiration from the PixelGameEngine HWButton struct by javidx9
    // https://github.com/OneLoneCoder/olcPixelGameEngine
    struct Key
    {
        bool pressed;
        bool held;
        bool released;
    };

    class inputs
    {
    public:
        inputs();
        void addKey(SDL_Keycode key);
        void removeKey(SDL_Keycode key);
        Key getKey(SDL_Keycode key) const;
        void update();
    private:
        std::vector<SDL_Keycode> cur_buttons;
        std::vector<SDL_Keycode> prev_buttons;
    };
};
// returns true if the input was just pressed
constexpr bool justPressed(bool prevInput, bool input) { return (!prevInput && input); }
#endif