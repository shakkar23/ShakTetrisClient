#pragma once
#include<array>
#include <string>
#ifndef TETRIS
#define TETRIS
#include "../../../Platform/SDL2/headers/RenderWindow.hpp"
#include "../../SDL2/headers/Game.hpp"

namespace Shakkar {

    class Tetris {
    public:
        explicit Tetris(std::string unlocalizedTetrisName): m_unlocalizedTetrisName(unlocalizedTetrisName){}
        virtual void gameLogic() = 0;
        virtual void render(RenderWindow& window) = 0;
    private:
        std::string m_unlocalizedTetrisName;
    };
};
#endif