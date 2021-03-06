//not my code#
#pragma once
#ifndef SHAK_RENDER_WINDOW
#define SHAK_RENDER_WINDOW

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "entity.hpp"

class autoTexture; //cpp bullshit

class RenderWindow {
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  

  int getRefreshrate();
  void cleanUp();
  void clear();
  void render(autoTexture& p_entity);
  void renderCopy(SDL_Texture* texture,
      const SDL_Rect* srcrect,
      const SDL_Rect* dstrect);
  void display(); 
  void getWindowSize(int& x, int&y);
  void setWindowSize(int x, int y);
  void renderFrame(std::vector<autoTexture *> & entities);
  SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  friend class autoTexture;
};

#endif