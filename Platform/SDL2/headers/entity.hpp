#pragma once
//not my code, but modified by me
#ifndef SHAK_ENTITY
#define SHAK_ENTITY

#include <SDL.h>
#include <SDL_image.h>

#include<utility>
#include<iostream>

#include "RenderWindow.hpp"

class RenderWindow; //cpp bullshit


//make sure to set the sprite at the very least! otherwise your png will not be shown
class autoTexture {
public:
	autoTexture(const char* filepath, RenderWindow &window);
	autoTexture();
  ~autoTexture();

  // keep this as { 0,0,0,0 } for taking in the entire png
  // otherwise you specify what section of the png you are taking in via the window you choose inside the 
  // x cord, y cord, x size, y size that you choose
  SDL_Rect textureRegion{};
  // the canvas of the window is by default a grid of 1920 by 1080 for standardization in position purposes, please use it 
  // data structure: x cord, y cord, x size, y size
  SDL_Rect sprite{};

  void Init(const char* filepath, RenderWindow &window);
  void unInit();
  SDL_Texture *getTex();
  SDL_Rect getTextureRegion();
  SDL_Rect getSprite(); 


  autoTexture(const autoTexture& other) = delete;               // Copy constructor
  autoTexture& operator=(const autoTexture& other) = default;  // Copy assignment operator
  autoTexture(autoTexture&& other) noexcept : textureRegion(other.textureRegion), sprite(other.sprite) {
	  other.sprite = {0,0,0,0}; other.textureRegion = {0,0,0,0};
	  std::swap(this->tex, other.tex);
  } // move constructor
  autoTexture& operator=(autoTexture&& other) noexcept = default;// move assignment operator
  
private:
  SDL_Texture* tex{};
  void loadTexture(const char* p_filePath, RenderWindow &window);
};

#endif