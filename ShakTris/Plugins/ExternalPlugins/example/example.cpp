
#include "example.hpp"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

demo::demo() : Shakkar::Tetris("bruh") {
    
    isPlaying = true;
}
void demo::Init(RenderWindow& window) {
    game.Init(window);
}

static int iter{};
void demo::gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) {
    if (iter != 2500) // game starting delay, except I suck
    {
        iter++;
        return;
    }

    game.gameLogic(input, prevInput);
}

void demo::render(RenderWindow& window)  {
    
    game.render(window);
}



PLUGIN_SETUP("example", "Shakkar23", "ok so basically this is an example and its for example purposes, and its an example that is used for being an example") {
    printf("initializing example plugin...\n");
    
    Shakkar::Plugins::addorig<demo>();
    Shakkar::Plugins::getEntries().back()->Init((*(RenderWindow*)window));
    
}