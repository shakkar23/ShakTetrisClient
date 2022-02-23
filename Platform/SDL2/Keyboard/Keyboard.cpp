
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include"Keyboard.hpp"


namespace Shakkar {
    namespace Keyboard {
        void pressKey(const SDL_Scancode scan, Shakkar::inputBitmap &input) {
            if (scan == SDL_Scancode::SDL_SCANCODE_A)
            {
                input.setLeft();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_D)
            {
                input.setRight();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.setRotRight();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.setRotLeft();
            }
            
            else if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.setRot180();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.setHold();
            }

            else if(scan==SDL_Scancode::SDL_SCANCODE_W)
            {
                input.setHardDrop();
            }
            
            else if (scan == SDL_Scancode::SDL_SCANCODE_S)
            {
                input.setSoftDrop();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_X)
            {
                input.setSonicDrop();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.setMenuUp();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.setMenuLeft();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.setMenuRight();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.setMenuDown();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_RETURN)
            {
                input.setMenuSelect();
            }
            
        }
        void unpressKey( const SDL_Scancode scan, Shakkar::inputBitmap &input) {
            if (scan == SDL_Scancode::SDL_SCANCODE_A)
            {
                input.unsetLeft();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_D)
            {
                input.unsetRight();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.unsetRotRight();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.unsetRotLeft();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.unsetRot180();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.unsetHold();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_W)
            {
                input.unsetHardDrop();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_S)
            {
                input.unsetSoftDrop();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_X)
            {
                input.unsetSonicDrop();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_UP)
            {
                input.unsetMenuUp();
            }
            
            else if (scan == SDL_Scancode::SDL_SCANCODE_LEFT)
            {
                input.unsetMenuLeft();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_RIGHT)
            {
                input.unsetMenuRight();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_DOWN)
            {
                input.unsetMenuDown();
            }

            else if (scan == SDL_Scancode::SDL_SCANCODE_RETURN)
            {
                input.unsetMenuSelect();
            }


        }
    }
}
