//not my code, but modified by me
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<utility>
#include<iostream>

#include "RenderWindow.hpp"

class autoTexture {
public:
	autoTexture(const char* filepath, RenderWindow window);
	autoTexture();
  ~autoTexture();

  void Init(const char* filepath, RenderWindow window);

  void autoTexture::unInit();
  SDL_Texture *getTex();
  SDL_Rect getTextureRegion();
  SDL_Rect getSprite(); 
  autoTexture(const autoTexture& other) = delete;               // Copy constructor
  autoTexture& operator=(const autoTexture& other) {};  // Copy assignment operator
  autoTexture(autoTexture&& other) noexcept : sprite(other.sprite), textureRegion(other.textureRegion){
	  other.sprite = {0,0,0,0}; other.textureRegion = {0,0,0,0};
	  std::swap(this->tex, other.tex);
  }// move constructor
  autoTexture& operator=(autoTexture&& other) noexcept {}
  SDL_Rect textureRegion{};
  SDL_Rect sprite{};
private:

  SDL_Texture* tex{};
  void loadTexture(const char* p_filePath, RenderWindow window);
};