
#include "example.hpp"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
demo::demo() : Shakkar::Tetris() {
    
    isPlaying = true;
}

//override
void demo::Init(RenderWindow& window) {
    game.Init(window);

    //handling the fact that this is also simultaneously the ReInit() function, TODO: change later for it to be a stand alone function
    if (this->alreadyInitialized) {
        game.reload();
        isPlaying = true;
    }

    this->alreadyInitialized = true;

}

//override
void demo::gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) {
    
    if ((!prevInput.menuSelect) && (input.menuSelect))
        isPlaying = false;

    game.gameLogic(input, prevInput);
}

//override
void demo::render(RenderWindow& window)  {
    
    game.render(window);
}


////         name of plugin     author           description?
PLUGIN_SETUP("example",         "Shakkar23",    "example plugin lets GOOOO") {
    Shakkar::Plugins::addorig<demo>();
    Shakkar::Plugins::getEntries().back()->Init((*(RenderWindow*)window));
}