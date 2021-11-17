
#include "example.hpp"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

demo::demo() : Shakkar::Tetris("bruh") {
    
    isPlaying = true;
}
void demo::Init(RenderWindow& window) {
    game.Init(window);

    //handling the fact that this is also simultaneously the ReInit() function, TODO: change later for it to be a stand alone function
    if (this->alreadyInitialized) {
        game.reload();
        isPlaying = true;
    }

    this->alreadyInitialized = true;

}

void demo::gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) {
    
    if ((!prevInput.menuSelect) && (input.menuSelect))
        isPlaying = false;

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