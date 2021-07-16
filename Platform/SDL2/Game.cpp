#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "headers/RenderWindow.hpp"
#include "headers/entity.hpp"

int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError()
              << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

  RenderWindow window("Shaktris", 480, 360); // tiny window, will be full screenable later hopefully
  std::cout << window.getRefreshrate() << std::endl;
  SDL_Texture *grassTexture = window.loadTexture("Asset/Sprites/invertedshak.png");

  std::vector<Entity> entitiees = {Entity(0, 0, grassTexture)};
  

  bool gameRunning = true;

  SDL_Event event;

  while (gameRunning) {

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          gameRunning = false;
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_LEFT)
            std::cout << "left" << std::endl;
        }
      }
      std::cout << "done" << std::endl;
    window.clear();
    for (Entity &e : entitiees) {
      window.render(e);
    }
    window.display();
  }

  window.cleanUp();
  SDL_Quit();

  return 0;
}