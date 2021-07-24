//not my code, but modified by me
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<utility>
#include<iostream>

#include "RenderWindow.hpp"

class autoTexture {
public:
	autoTexture(int pos_x, int pos_y, const char* filepath, int size_x, int size_y, RenderWindow window);
	autoTexture();
  ~autoTexture();

  void Init(int pos_x, int pos_y, const char* filepath, int size_x, int size_y, RenderWindow window);

  void autoTexture::unInit();
  int getXpos();
  int getYpos();
  SDL_Texture *getTex();
  SDL_Rect getTextureRegion();
  SDL_Rect getSprite(); 
  autoTexture(const autoTexture& other) = delete;               // Copy constructor
  autoTexture& operator=(const autoTexture& other) {};  // Copy assignment operator
  autoTexture(autoTexture&& other) noexcept : sprite(other.sprite), textureRegion(other.textureRegion){
	  other.x = 0; other.y = 0; other.sprite = { 0,0,0,0 }; other.textureRegion = { 0,0,0,0 };
	  std::swap(this->tex, other.tex); 

  }// move constructor
  autoTexture& operator=(autoTexture&& other) noexcept {}
private:
  SDL_Rect textureRegion{};
  SDL_Rect sprite{};

  SDL_Texture* tex{};
  void loadTexture(const char* p_filePath, RenderWindow window);
};