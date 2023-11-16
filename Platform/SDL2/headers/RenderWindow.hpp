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
  ~RenderWindow();
    // window related
    int getRefreshrate();
    void getWindowSize(int& x, int& y);
    void setWindowSize(int x, int y);
    // drawing related
    bool render(SDL_Rect src, SDL_Rect dst, SDL_Texture* tex);
    void renderCopy(SDL_Texture* texture,
        const SDL_Rect* srcrect,
        const SDL_Rect* dstrect);
private:
    void display();
public:
    void clear();
    void drawCircle(int x, int y, int r);
    void drawRect(SDL_Rect rec);
    // utility
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void getDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Renderer* getRenderer();
    friend class Texture;
    friend class SurfaceTexture;
    friend class gameManager;
};

#endif