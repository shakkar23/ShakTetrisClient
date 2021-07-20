
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include"Keyboard.hpp"


namespace Shakkar {
    namespace Keyboard {
        void pressKey( SDL_Scancode scan){
            if (scan == SDL_Scancode::SDL_SCANCODE_A)
            {
                input.setLeft();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_D)
            {
                input.setRight();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.setRotRight();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.setRotLeft();
            }
            
            if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.setRot180();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.setHold();
            }

            if(scan==SDL_Scancode::SDL_SCANCODE_W)
            {
                input.setHardDrop();
            }
            
            if (scan == SDL_Scancode::SDL_SCANCODE_W)
            {
                input.setSoftDrop();
            }

            
        }
        void unpressKey( SDL_Scancode scan) {
            if (scan == SDL_Scancode::SDL_SCANCODE_A)
            {
                input.unsetLeft();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_A)
            {
                input.unsetRight();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.unsetRotRight();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.unsetRotLeft();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.unsetRot180();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.unsetHold();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_W)
            {
                input.unsetHardDrop();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_S)
            {
                input.unsetSoftDrop();
            }

        }
    }
}
