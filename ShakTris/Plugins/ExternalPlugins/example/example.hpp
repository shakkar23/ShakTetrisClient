#pragma once
#include "../../PluginHeaders/Tetris.hpp"
#include "../../PluginHeaders/PluginRegistry.hpp"
#include "Tetris.hpp"

class demo : public Shakkar::Tetris {
public:
    demo();
    ~demo() {}

    void gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) override;
    void render(RenderWindow& window) override;
    void Init(RenderWindow& window) override;
    
private:
    Game game;

    bool alreadyInitialized = false;
};
