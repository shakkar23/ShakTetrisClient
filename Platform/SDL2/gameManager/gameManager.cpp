#include "gameManager.hpp"

void gameManager::Init(RenderWindow& window) {
    if (!mainMenu->isInitialized) mainMenu->Init(window); submenuWasDeleted = false;
}

bool gameManager::gameLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
    if (!submenuWasDeleted) {
        this->menuLogic(input, prevInput);
        return true; // worked
    }
    else {
        mainMenu = nullptr;
        return false; // mainmenu was exited, exit game
    }

}
void gameManager::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
        mainMenu->menuLogic(input, prevInput);
}
void gameManager::render(RenderWindow &window) {
    mainMenu->render(window);
    window.display();
}
gameManager GameManager;