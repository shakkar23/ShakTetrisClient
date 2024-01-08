#pragma once
#include "../../PluginHeaders/Tetris.hpp"
#include "../../PluginHeaders/PluginRegistry.hpp"
#include "Tetris.hpp"

class demo : public Shakkar::Tetris {
public:
    demo();
    ~demo() {}

    void gameLogic(const Shakkar::inputs& input) override;
    void render(RenderWindow& window) override;
    void Init(RenderWindow& window) override;
    void updateSettings(uint32_t das, uint32_t arr) override;
    
private:
    Game game;

    bool alreadyInitialized = false;
};
