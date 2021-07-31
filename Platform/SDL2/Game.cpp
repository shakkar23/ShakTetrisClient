#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "headers/entity.hpp"
#include "headers/RenderWindow.hpp"
#include "Keyboard/Keyboard.hpp"
#include "Menus/Menus.hpp"
#define DEFAULT_SCREEN_WIDTH 1080
#define DEFAULT_SCREEN_HEIGHT 1920
int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
              << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

  RenderWindow window("Shaktris", 480, 272); // tiny window, will be full screenable now :sunglasses: // later hopefully
  
//  std::cout << window.getRefreshrate() << std::endl; 

  bool gameRunning = true;
  SDL_Event event;

  //everything above this is for initializing the game, and its assets, please dont initialize everything the game uses at once
  gameManager game;

  //std::vector<autoTexture *> entitiees = {&game.mainMenu.invertedShak,&game.mainMenu.blankMenu,&game.mainMenu.highlightedMenu}; //rendered from left to right
  bool shouldDisplay = false; // rendering constantly, and not actually displaying causes memory to stack higher and higher until the frames can be shown
  bool sizechanged = false;
  while (gameRunning) {

      while (SDL_PollEvent(&event)) {

          if (event.type == SDL_WINDOWEVENT) {
              if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                  shouldDisplay = true;
              }else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
                  shouldDisplay = false;
              }else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                  sizechanged = true; 
              }
          }else if (event.type == SDL_QUIT)
              gameRunning = false;
          else if ((event.key.type == SDL_KEYDOWN) || (event.key.type == SDL_KEYUP)) {
              if (event.key.state == SDL_PRESSED) {
                  if (event.key.repeat) continue;
                  Shakkar::Keyboard::pressKey(event.key.keysym.scancode);

                  //std::cout << "keydown" << ++isanykeydown << std::endl; //check for what key is pressed, and then up this value
                  std::cout << "Physical" << SDL_GetScancodeName(event.key.keysym.scancode) << " key acting as" << SDL_GetKeyName(event.key.keysym.sym) << " key" <<
                      std::endl << Shakkar::input.menuDown;
              }
              else {
                  Shakkar::Keyboard::unpressKey(event.key.keysym.scancode);
              }
          }

      } 

      if (!shouldDisplay) { // skip frames that cant be shown due to window not currently accepting frames to display
          //window.renderFrame();
          game.menuLogic(Shakkar::input);

      }
          window.display();
  }

  window.cleanUp();
  SDL_Quit();

  return 0;
}