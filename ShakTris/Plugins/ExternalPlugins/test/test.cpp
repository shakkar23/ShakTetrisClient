
#include "test.hpp"
#include <string>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

demo::demo() : Shakkar::Tetris() {
    
    isPlaying = true;
}

void demo::updateSettings(uint32_t das, uint32_t arr) {
}
//override
void demo::Init(RenderWindow& window) {

    //handling the fact that this is also simultaneously the ReInit() function, TODO: change later for it to be a stand alone function
    if (this->alreadyInitialized) {
        isPlaying = true;
    }

    this->alreadyInitialized = true;

    int windowWidth, windowHeight;
    window.getWindowSize(windowWidth, windowHeight);
    x = windowWidth / 2;
    y = windowHeight / 2;
}

//override
void demo::gameLogic(const Shakkar::inputs& input) {
    Shakkar::Key menuExit = input.getKey(SDLK_ESCAPE);
    if (menuExit.pressed)
        isPlaying = false;

}

//override
void demo::render(RenderWindow& window) {
    const int CircleWidth = 20;
    int windowWidth, windowHeight;
    window.getWindowSize(windowWidth, windowHeight);

    Uint8 r, g, b, a;
    window.getDrawColor(r, g, b, a);

    window.clear();


    window.setDrawColor(255, 0, 0, 255);



    x += dx;
    y += dy;


    if ((x + CircleWidth) >= windowWidth) {
        int overflow = (x + CircleWidth) - windowWidth;
        x -= overflow;

        dx = -abs(dx);
    }
    else if ((x - CircleWidth) <= 0) {
        int overflow = abs(x - CircleWidth);
        x += overflow;

        dx = abs(dx);
    }

    if ((y + CircleWidth) >= windowHeight) {
        int overflow = (y + CircleWidth) - windowHeight;
        y -= overflow;

        dy = -abs(dy);
    }
    else if ((y - CircleWidth) <= 0) {
        int overflow = abs(y - CircleWidth);
        y += overflow;

        dy = abs(dy);
    }

    dy += 1;
    SDL_Rect rect{
        x - CircleWidth,
		y - CircleWidth,
		CircleWidth * 2,
		CircleWidth * 2
    };

    window.drawRect(rect);

    window.setDrawColor(r,g,b,a);
}


////         name of plugin     author           description?
PLUGIN_SETUP("test",         "Shakkar23",    "test plugin") {
    Shakkar::Plugins::addorig<demo>();
}