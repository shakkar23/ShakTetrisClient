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
  SDL_Rect src;
  src.x = p_entity.getSprite().x;
  src.y = p_entity.getSprite().y;
  src.w = p_entity.getSprite().w;
  src.h = p_entity.getSprite().h;

  SDL_Rect dst;
  dst.x = p_entity.getXpos();
  dst.y = p_entity.getYpos();
  dst.w = p_entity.getSprite().w;
  dst.h = p_entity.getSprite().h;
  int error = SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
  if (error != 0)
      std::cout << "wtf" << std::endl << SDL_GetError() << std::endl;
  else
      std::cout << "flushed" << std::endl;
 
}

void RenderWindow::display() { SDL_RenderPresent(renderer); }

