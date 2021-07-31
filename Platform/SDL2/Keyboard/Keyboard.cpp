
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include"Keyboard.hpp"


namespace Shakkar {
    namespace Keyboard {
        void pressKey(SDL_Scancode scan, Shakkar::inputBitmap &input) {
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

            if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.setMenuUp();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.setMenuLeft();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.setMenuRight();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.setMenuDown();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_RETURN)
            {
                input.setMenuSelect();
            }
            
        }
        void unpressKey( SDL_Scancode scan, Shakkar::inputBitmap &input) {
            if (scan == SDL_Scancode::SDL_SCANCODE_A)
            {
                input.unsetLeft();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_D)
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

            if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.unsetMenuUp();
            }
            
            if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.unsetMenuLeft();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.unsetMenuRight();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.unsetMenuDown();
            }

            if (scan == SDL_Scancode::SDL_SCANCODE_RETURN)
            {
                input.unsetMenuSelect();
            }


        }
    }
}
