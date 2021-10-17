#pragma once
//not my code, but modified by me
#ifndef SHAK_ENTITY
#define SHAK_ENTITY

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<utility>
#include<iostream>

#include "RenderWindow.hpp"

class RenderWindow; //cpp bullshit


//make sure to set the sprite at the very least! otherwise your png will not be shown
class autoTexture {
public:
	autoTexture(const char* filepath, RenderWindow window);
	autoTexture();
  ~autoTexture();

  // keep this as { 0,0,0,0 } for taking in the entire png
  SDL_Rect textureRegion{};
  // the canvas of the window is by default a grid of 1920 by 1080 for standardization in position purposes, please use it
  SDL_Rect sprite{};

  void Init(const char* filepath, RenderWindow window);
  void unInit();
  SDL_Texture *getTex();
  SDL_Rect getTextureRegion();
  SDL_Rect getSprite(); 


  autoTexture(const autoTexture& other) = delete;               // Copy constructor
  autoTexture& operator=(const autoTexture& other) {};  // Copy assignment operator
  autoTexture(autoTexture&& other) noexcept : sprite(other.sprite), textureRegion(other.textureRegion){
	  other.sprite = {0,0,0,0}; other.textureRegion = {0,0,0,0};
	  std::swap(this->tex, other.tex);
  }// move constructor
  autoTexture& operator=(autoTexture&& other) noexcept {}// move assignment operator
  
private:
  SDL_Texture* tex{};
  void loadTexture(const char* p_filePath, RenderWindow window);
};

#endif