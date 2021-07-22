//not my code
#include "headers/entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

autoTexture::autoTexture() {}
autoTexture::autoTexture(int pos_x, int pos_y, const char* filepath, int size_x, int size_y, RenderWindow window): x(pos_x), y(pos_y) {
    this->currentFrame.x = pos_x;
    this->currentFrame.y = pos_y;
    this->currentFrame.w = size_x;
    this->currentFrame.h = size_y;
    this->loadTexture(filepath, window);
}

void autoTexture::Init(int pos_x, int pos_y, const char* filepath, int size_x, int size_y, RenderWindow window)
{
    if (tex != nullptr) return;
    x=pos_x; y=pos_y;
    this->currentFrame.x = pos_x;
    this->currentFrame.y = pos_y;
    this->currentFrame.w = size_x;
    this->currentFrame.h = size_y;
    this->loadTexture(filepath, window);

}

void autoTexture::unInit(){
    if (tex == nullptr) return;
    x = 0; y = 0;
    this->currentFrame.x = 0;
    this->currentFrame.y = 0;
    this->currentFrame.w = 0;
    this->currentFrame.h = 0;
    SDL_DestroyTexture(tex);
    tex = nullptr;
}
autoTexture::~autoTexture() {
    std::cout << "this shouldnt happen" << std::endl;
    if (tex == nullptr) return;
    SDL_DestroyTexture(tex);
}

int autoTexture::getXpos() { return x; }
int autoTexture::getYpos() { return y; }

SDL_Texture *autoTexture::getTex() { return tex; }

SDL_Rect autoTexture::getCurrentFrame() { return currentFrame; }

void autoTexture::loadTexture(const char* p_filePath, RenderWindow window) {
    
    this->tex = IMG_LoadTexture(window.renderer, p_filePath);
    std::cout << SDL_GetError()<<std::endl;
    if (this->tex == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

}