#pragma once

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

    struct Mouse {
		int32_t x;
		int32_t y;

		int32_t dx;
		int32_t dy;

		int32_t wx;
        int32_t wy;

		bool left_held;
        bool left_pressed;
		bool right_held;
        bool right_pressed;
		bool middle_held;
        bool middle_pressed;
	};

    class inputs
    {
    public:
        inputs();
        void updateMousePos(int32_t x, int32_t y, int32_t dx, int32_t dy);
        void updateMouseWheel(int32_t wx, int32_t wy, int32_t dwx);
        void updateMouseButtons(uint32_t which, bool state);
        void addKey(SDL_Keycode key);
        void removeKey(SDL_Keycode key);
        
        Mouse getMouse() const;
        Key getKey(SDL_Keycode key) const;
        void update();
    private:
        std::vector<SDL_Keycode> cur_buttons;
        std::vector<SDL_Keycode> prev_buttons;
        Mouse mouse;
    };
};
// returns true if the input was just pressed
constexpr bool justPressed(bool prevInput, bool input) { return (!prevInput && input); }
