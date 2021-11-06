#pragma once
#include "../../PluginHeaders/Tetris.hpp"
#include "../../PluginHeaders/PluginRegistry.hpp"
#include "Tetris.hpp"

class demo : public Shakkar::Tetris {
public:
    demo();

    void gameLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) override;
    void render(RenderWindow& window) override;
private:
    Game game;
};
