//not my code#
#pragma once

#ifndef SHAK_RENDER_WINDOW
#define SHAK_RENDER_WINDOW

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture;

class RenderWindow {
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  

  int getRefreshrate();
  void cleanUp();
  void clear();
  bool render(SDL_Rect src, SDL_Rect dst, SDL_Texture* tex);
  void renderCopy(SDL_Texture* texture,
      const SDL_Rect* srcrect,
      const SDL_Rect* dstrect);
  void display(); 
  void getWindowSize(int& x, int&y);
  void setWindowSize(int x, int y);

  SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_Renderer *getRenderer();
  friend class Texture;
  friend class SurfaceTexture;
};

#endif