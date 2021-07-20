#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "headers/entity.hpp"
#include "headers/RenderWindow.hpp"
#include "Keyboard/Keyboard.hpp"

int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
              << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

  RenderWindow window("Shaktris", 480, 360); // tiny window, will be full screenable later hopefully
  std::cout << window.getRefreshrate() << std::endl;
  autoTexture invertedShak; invertedShak.Init(0, 0, "Asset/Sprites/invertedshak.png", 480, 360, window);
  //SDL_Texture *invertedshak     = window.loadTexture("Asset/Sprites/invertedshak.png");
  autoTexture blankMenu;blankMenu.Init(0, 0, "Asset/Sprites/blankmenu.png", 480, 360, window);
  autoTexture highlightedMenu; highlightedMenu.Init(0, 0, "Asset/Sprites/highlightedmenu.png", 480, 360, window);


  std::vector<autoTexture> entitiees = {invertedShak, blankMenu };
  //everything above this is for initializing the game, and its assets, please dont initialize everything the game uses at once

  


  bool gameRunning = true;
  SDL_Event event;
  // this is going to be a stupid way of keeping track of inputs
  int isanykeydown{}; // debug var

  while (gameRunning) {
      //if (isanykeydown < 0) isanykeydown = 0;

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          gameRunning = false;//(event.type == SDL_KEYDOWN) &&
        if ((event.key.type == SDL_KEYDOWN) || (event.key.type == SDL_KEYUP)) {
            if (event.key.state == SDL_PRESSED) {
                if (event.key.repeat) continue;
                Shakkar::Keyboard::pressKey(event.key.keysym.scancode);
                
                //std::cout << "keydown" << ++isanykeydown << std::endl; //check for what key is pressed, and then up this value
                std::cout <<"Physical" << SDL_GetScancodeName(event.key.keysym.scancode) <<" key acting as" <<SDL_GetKeyName(event.key.keysym.sym) <<  " key" <<
                    std::endl;
            }
            else  {
                //std::cout << "keyup" << --isanykeydown << std::endl;
            }
        }
      }
    window.clear();
    for (autoTexture &e : entitiees) {
      window.render(e);
    }
    window.display();
  }

  window.cleanUp();
  SDL_Quit();

  return 0;
}