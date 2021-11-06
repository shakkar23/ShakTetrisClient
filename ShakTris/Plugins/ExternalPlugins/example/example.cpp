
#include "example.hpp"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

demo::demo() : Shakkar::Tetris("bruh") {
    int i;
    i = 2;
}

static int iter{};
void demo::gameLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
    if (iter != 2500)
    {
        iter++;
        return;
    }

    game.gameLogic(input, prevInput);
}

void demo::render(RenderWindow& window)  {

}



PLUGIN_SETUP("john tronathon", "Shakkar23", "ok so basically this is an example and its for example purposes, and its an example that is used for being an example") {

    Shakkar::Plugins::add<demo>();
    
}