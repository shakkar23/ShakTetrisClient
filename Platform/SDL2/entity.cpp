//not my code
#include "headers/entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

autoTexture::autoTexture() {}
autoTexture::autoTexture(const char* filepath, RenderWindow &window) {
    this->loadTexture(filepath, window);
}

void autoTexture::Init(const char* filepath, RenderWindow &window)
{
    if (tex != nullptr) return;
    this->loadTexture(filepath, window);

}

void autoTexture::unInit(){
    if (tex == nullptr) return;
    this->sprite.x = 0;
    this->sprite.y = 0;
    this->sprite.w = 0;
    this->sprite.h = 0;
    this->textureRegion.x = 0;
    this->textureRegion.y = 0;
    this->textureRegion.w = 0;
    this->textureRegion.h = 0;
    SDL_DestroyTexture(tex);
    tex = nullptr;
}

autoTexture::~autoTexture() {
    //std::cout << "this shouldnt happen" << std::endl;
    if (tex == nullptr) return;
    SDL_DestroyTexture(tex);
}

SDL_Texture* autoTexture::getTex() { return tex; }
SDL_Rect autoTexture::getSprite() { return sprite; }
SDL_Rect autoTexture::getTextureRegion() { return textureRegion; }

void autoTexture::loadTexture(const char* p_filePath, RenderWindow &window) {
    
    this->tex = IMG_LoadTexture(window.renderer, p_filePath);
    std::cout << SDL_GetError()<<std::endl;
    if (this->tex == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

}

void autoTexture::modifyTex(Uint8 a) {

    SDL_SetTextureAlphaMod(tex, a);
   
}