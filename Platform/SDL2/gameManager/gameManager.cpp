#include "gameManager.hpp"

void gameManager::Init(RenderWindow& window) { if (!mainMenu->isInitialized) mainMenu->Init(window); }
void gameManager::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
    mainMenu->menuLogic(input, prevInput);
}
void gameManager::render(RenderWindow window) {
    mainMenu->render(window);
    window.display();
}
gameManager GameManager;