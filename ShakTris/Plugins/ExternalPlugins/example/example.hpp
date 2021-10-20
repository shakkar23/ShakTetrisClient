#pragma once
#include "../../PluginHeaders/Tetris.hpp"
#include "../../PluginHeaders/PluginRegistry.hpp"

enum class PieceType : uint_fast8_t
{
    //special types
    empty,
    line_clear,

    //actual pieces
    S, Z, J, L, T, O, I,
};


class demo : public Shakkar::Tetris {
public:

    demo();
    void gameLogic() override;
    void render(RenderWindow& window) override;
private:
    std::array< std::array<PieceType, 20>, 10> board{};
};

enum class RotationDirection : uint_fast8_t
{
    North,
    East,
    South,
    West
};

struct Piece {
    int_fast8_t x{};
    int_fast8_t y{};
    PieceType kind{};
    RotationDirection spin{};
    Piece = delete;
    Piece(PieceType kind, int_fast8_t x = 4, int_fast8_t y = 20, RotationDirection spin = RotationDirection::North) {
        this->kind = kind;
        this->x = x;
        this->y = y;
        this->spin = spin;
    }

    void rotate() {}

};