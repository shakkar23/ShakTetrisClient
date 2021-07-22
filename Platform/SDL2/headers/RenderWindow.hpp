//not my code#
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class autoTexture;

class RenderWindow {
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  

  int getRefreshrate();
  void cleanUp();
  void clear();
  void render(autoTexture &p_entity);
  void display(); 

private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  friend class autoTexture;
};