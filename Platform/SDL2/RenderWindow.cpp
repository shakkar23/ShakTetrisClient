//not my code
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "headers/entity.hpp"
#include "headers/RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL) {
  window =
      SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (window == NULL) {
    std::cout << "Window failed to init. Error: " << SDL_GetError()
              << std::endl;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_RenderSetLogicalSize(this->renderer, 1920 , 1080);

}

int RenderWindow::getRefreshrate() {
  int displayIndex = SDL_GetWindowDisplayIndex(window);
  SDL_DisplayMode mode;
  SDL_GetDisplayMode(displayIndex, 0, &mode);
  return mode.refresh_rate;
}


void RenderWindow::cleanUp() { SDL_DestroyWindow(window); }

void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::render(autoTexture& p_entity) {
  SDL_Rect src = p_entity.getTextureRegion();

  SDL_Rect dst = p_entity.getSprite();
  auto checkIfSet = [&](SDL_Rect box) {if ((box.x == 0) && (box.y == 0) && (box.w == 0) && (box.h == 0)) return true; else return false; };
  
  int error = SDL_RenderCopy(renderer, p_entity.getTex(), (checkIfSet(src)) ? NULL : &src, &dst);
  if (error != 0)
      std::cout << "wtf" << std::endl << SDL_GetError() << std::endl;
  else
      ;//std::cout << "flushed" << std::endl;
 
}

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::getWindowSize(int& x, int& y) {
    SDL_GetWindowSize(this->window, &x, &y);
}

void RenderWindow::setWindowSize(int x, int y) {
    SDL_SetWindowSize(this->window, x, y);
}
void RenderWindow::renderFrame(std::vector<autoTexture *> & entities) {
    // skip frames that cant be shown due to window not currently accepting frames to display
        this->clear();
        for (autoTexture *e : entities) {
            this->render(*e);
        
    }
}
