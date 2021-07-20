//not my code, but modified by me
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RenderWindow.hpp"
#include<utility>
#include<iostream>

class autoTexture {
public:
	autoTexture();
  ~autoTexture();

  void Init(int pos_x, int pos_y, const char* filepath, int size_x, int size_y, RenderWindow window);
  int getXpos();
  int getYpos();
  SDL_Texture *getTex();
  SDL_Rect getCurrentFrame();
  
private:
  int x{}, y{};

  SDL_Rect currentFrame{};
  SDL_Texture* tex{};
  void loadTexture(const char* p_filePath, RenderWindow window);
};