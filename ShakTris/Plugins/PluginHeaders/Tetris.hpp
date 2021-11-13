#pragma once
#include<array>
#include <string>
#ifndef TETRIS
#define TETRIS
#include "../../../Platform/SDL2/headers/RenderWindow.hpp"
#include "../../../Platform/SDL2/headers/Game.hpp"
#include "../../../ShakTris/Input/Input.hpp"


namespace Shakkar {

    class Tetris {
    public:
        explicit Tetris(const std::string &unlocalizedTetrisName): m_unlocalizedTetrisName(unlocalizedTetrisName){}
        virtual void gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) = 0;
        virtual void render(RenderWindow& window) = 0;
        virtual void Init(RenderWindow& window) = 0;
        bool isPlaying = false;
    private:
        std::string m_unlocalizedTetrisName;
    };
};
#endif