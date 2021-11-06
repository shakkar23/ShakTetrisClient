#pragma once

#include "PieceDefs.hpp"
#include "Platform\SDL2\headers\Game.hpp""
#include <vector>

const int half(int i) {
    return i / 2;
}

const int BOARDWIDTH = 10;
const int BOARDHEIGHT = 20;


class Board;
class Piece {
public:
    Piece(PieceType kind, int_fast8_t x = 4 - half(PIECEWIDTH), int_fast8_t y = 19 - half(PIECEHEIGHT), RotationDirection spin = RotationDirection::North) {
        this->kind = kind;
        setX(x); setY(y);
        this->spin = spin;
        for (size_t w = 0; w < PIECEWIDTH; w++)
        {
            for (size_t h = 0; h < PIECEHEIGHT; h++)
            {
                piecedef[w][h] = PieceDefinition[PieceTypeToColorType(kind)][w][h];
            }
        }
        switch (spin)
        {
        case North:
            break;
        case East:
            rotatePieceMatrixRight();
            break;
        case South:
            rotatePieceMatrixRight(); rotatePieceMatrixRight();
            break;
        case West:
            rotatePieceMatrixRight(); rotatePieceMatrixRight(); rotatePieceMatrixRight();
            break;
        default:
            break;
        }
    }
    Piece() = delete;

    //props to geeksforgeeks for this function, here is the link I took it from
    // https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/

    friend Board;

    //rotates the piece 90 degrees to the right
    void rotatePieceMatrixRight()
    {
        // Consider all squares one by one
        for (int x = 0; x < PIECEWIDTHANDHEIGHT / 2; x++) {
            // Consider elements in group
            // of 8 in current square
            for (int y = x; y < PIECEWIDTHANDHEIGHT - x - 1; y++) {
                // Store current cell in
                // temp variable
                ColorType temp = piecedef[x][y];

                // Move values from right to top
                piecedef[x][y] = piecedef[y][PIECEWIDTHANDHEIGHT - 1 - x];

                // Move values from bottom to right
                piecedef[y][PIECEWIDTHANDHEIGHT - 1 - x]
                    = piecedef[PIECEWIDTHANDHEIGHT - 1 - x][PIECEWIDTHANDHEIGHT - 1 - y];

                // Move values from left to bottom
                piecedef[PIECEWIDTHANDHEIGHT - 1 - x][PIECEWIDTHANDHEIGHT - 1 - y]
                    = piecedef[PIECEWIDTHANDHEIGHT - 1 - y][x];

                // Assign temp to left
                piecedef[PIECEWIDTHANDHEIGHT - 1 - y][x] = temp;
            }
        }
    }

    void setX(size_t setter) {
        x = setter;
        realX = setter + half(PIECEWIDTH);
    }
    void setY(size_t setter) {
        y = setter;
        realY = setter + half(PIECEWIDTH);
    }
    int_fast8_t x{};
    int_fast8_t y{};
    int_fast8_t realX{};
    int_fast8_t realY{};
    PieceType kind{};
    RotationDirection spin{};
    std::array< std::array<ColorType, PIECEHEIGHT>, PIECEWIDTH> piecedef{};
    //ColorType piecedef[PIECEWIDTH][PIECEHEIGHT];

};

#include "rotation_constants.hpp"
class Board {
public:
    Board() {
        for (size_t w = 0; w < BOARDWIDTH; w++)
        {
            for (size_t h = 0; h < BOARDHEIGHT; h++)
            {
                board.at(w).at(h) = empty;
            }
        }
    }
    void sonicDrop(Piece& piece) {
        while (trySoftDrop(piece));
    }

    bool trySoftDrop(Piece &piece) {
        piece.setY(piece.x--);
        if (isCollide(piece)) {
            piece.setY(piece.x++);
            return false;
        }
        return true;
    }

    bool tryRotateLeft(Piece piece) {
        if (piece.kind == PieceType::O)
            return true;
        piece.rotatePieceMatrixRight();
        piece.rotatePieceMatrixRight();
        piece.rotatePieceMatrixRight();
        for (int h = piece.y, PieceW = PIECEHEIGHT - 1; h < PIECEHEIGHT + piece.y; h++, PieceW--)// subtract the width cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int w = piece.x, PieceH = 0; w < PIECEWIDTH + piece.x; w++, PieceH++)
            {
                if ((((0 <= h) && (h < BOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    if ((board.at(w).at(h) != ColorType::empty) && (piece.piecedef[PieceW][PieceH] != ColorType::empty))
                        continue;
                    else {
                        piece.rotatePieceMatrixRight();
                        return false;
                    }
                }
            }
        }
    }


    bool tryRotate(Piece& piece, TurnDirection direction) {
        auto incrRot = [&]() {
            switch (piece.spin)
            {
            case North:
                piece.spin = East;
                break;
            case East:
                piece.spin = South;
                break;
            case South:
                piece.spin = West;
                break;
            case West:
                piece.spin = North;
                break;
            case number_of_RotationDirections:
                break;
            default:
                break;
            }
        };
        int_fast8_t x = piece.x; int_fast8_t y = piece.y;
        constexpr bool srs_plus = false;
        //
        if (direction == Right)
            piece.rotatePieceMatrixRight();
        else if (direction == Left)
        {
            piece.rotatePieceMatrixRight();
            piece.rotatePieceMatrixRight();
            piece.rotatePieceMatrixRight();
        }
        else if (direction == oneEighty)
        {
            piece.rotatePieceMatrixRight();
            piece.rotatePieceMatrixRight();
        }

        // spinclockwise should be a bool, but it can also be 2 as in rotating twice
        // in one frame aka 180 spin
        if (direction != TurnDirection::oneEighty) {
            const int(*pdata)[kicks][2] = wallkickdata[piece.spin];

            if (piece.kind == PieceType::I)
                pdata = srs_plus ? srsplusIwallkickdata[piece.spin] : Iwallkickdata[piece.spin];
            for (int iter_rot = 0; iter_rot < kicks; ++iter_rot) {
                piece.setX(x + (pdata[direction][iter_rot][0]));
                piece.setY(y + (pdata[direction][iter_rot][1]));

                if (!isCollide(piece)) {

                    if (direction == Right)
                        incrRot();
                    else if (direction == Left)
                    {
                        incrRot(); incrRot(); incrRot();
                    }

                    return true;
                }
            }
            piece.setX(x); piece.setY(y);
        }
        else {
            const int(*kickdata)[2] = wallkick180data[piece.spin];
            if (piece.kind == PieceType::I)
                kickdata = Iwallkick180data[piece.spin];

            for (int i = 0; i < kicks180; i++) {
                piece.setX(x + kickdata[i][0]);
                piece.setY(y + kickdata[i][1]);

                if (!isCollide(piece)) {
                    incrRot(); incrRot();
                    return true;
                }
            }
            piece.setX(x); piece.setY(y);
        }

        //rotate the matrix back if nothing worked
        if (direction == Right) {
            piece.rotatePieceMatrixRight();
            piece.rotatePieceMatrixRight();
            piece.rotatePieceMatrixRight();
        }
        else if (direction == Left)
            piece.rotatePieceMatrixRight();
        else if (direction == oneEighty)
        {
            piece.rotatePieceMatrixRight();
            piece.rotatePieceMatrixRight();
        }
        return false;
    }

    void setPiece(Piece piece) {
        for (int h = piece.y, PieceW = PIECEHEIGHT - 1; h < PIECEHEIGHT + piece.y; h++, PieceW--)// subtract the width cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int w = piece.x, PieceH = 0; w < PIECEWIDTH + piece.x; w++, PieceH++)
            {
                if ((((0 <= h) && (h < BOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    board.at(w).at(h) = piece.piecedef[PieceW][PieceH];
                }
            }
        }
    }

    bool isCollide(Piece piece) {
        for (int w = piece.x; w < PIECEWIDTH + piece.x; w++)// subtract the height cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int h = piece.y; h < PIECEHEIGHT + piece.y; h++)
            {
                if ((((0 <= h) && (h < BOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    int x = w - piece.x;
                    int y = 4 - h + piece.y;
                    ColorType pieceBlock = piece.piecedef[y][x];
                    if (pieceBlock != empty) // is the cell empty in the piece matrix is empty

                        if (board.at(w).at(h) != empty) // is the cell in the board matrix empty
                            return true;
                }
            }
        }
        return false;
    }

    constexpr const char colorTypeToString(ColorType bruh) {
        switch (bruh)
        {
        case S:
            return'S';
            break;
        case Z:
            return 'Z';
            break;
        case J:
            return 'J';
            break;
        case L:
            return'L';
            break;
        case T:
            return'T';
            break;
        case O:
            return'O';
            break;
        case I:
            return 'I';
            break;
        case empty:
        case line_clear:
        case number_of_ColorTypes:
        default:
            return '#';
        }
    }
#ifdef _DEBUG
    void printboard() {
        for (int_fast8_t h = BOARDHEIGHT - 1; h >= 0; h--)
        {
            for (int_fast8_t w = 0; w < BOARDWIDTH; w++)
            {

                std::cout << colorTypeToString(board.at(w).at(h));
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void printboardWithPiece(Piece piece) {
        for (int_fast8_t h = BOARDHEIGHT - 1; h >= 0; h--)
        {
            for (int_fast8_t w = 0; w < BOARDWIDTH; w++)
            {

                if (((piece.x <= w) && (w <= (piece.x + PIECEWIDTH - 1))) && ((piece.y <= h) && (h <= (piece.y + PIECEHEIGHT - 1))))
                {
                    ColorType block = piece.piecedef[4 - h + piece.y][w - piece.x];
                    if (block != empty)
                        std::cout << "0";
                    else
                        std::cout << colorTypeToString(board.at(w).at(h));

                }
                else
                    std::cout << colorTypeToString(board.at(w).at(h));

            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
#endif
    std::array< std::array<ColorType, BOARDHEIGHT>, BOARDWIDTH> board{};
};
class Game
{
public:

    Game();
    ~Game();

    void gameLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput);
    void render(RenderWindow& window);

private:
    Piece currentPiece{ PieceType::empty };
    std::vector<Piece> queue{};
    Board board;
};

Game::Game()
{
    //temp pieces
    queue.reserve(7);
    queue.emplace_back(Piece(PieceType::S));
    queue.emplace_back(Piece(PieceType::Z));
    queue.emplace_back(Piece(PieceType::J));
    queue.emplace_back(Piece(PieceType::L));
    queue.emplace_back(Piece(PieceType::T));
    queue.emplace_back(Piece(PieceType::O));
    queue.emplace_back(Piece(PieceType::I));
}

const static uint16_t softdropCountdownMAX = 4096; // 4096 cause thats what ppt uses according to fug
static uint16_t softdropCountdown = softdropCountdownMAX;

void Game::gameLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
    if (currentPiece.kind != PieceType::empty)
    {
        if ((input.hardDrop) && !(prevInput.hardDrop))
        {
            board.sonicDrop(currentPiece);
            board.setPiece(currentPiece);
            currentPiece.kind = PieceType::empty;
        }
        else {


            if (softdropCountdown == 0)
            {
                //softdrop pls
                if (!board.trySoftDrop(currentPiece)) {
                    board.setPiece(currentPiece);
                    currentPiece.kind = PieceType::empty;
                }
                softdropCountdown = softdropCountdownMAX;
            }
            else {
                // 20 is another number ppt uses according to fug, and the 60 is for the updates a second ppt uses in their game
                softdropCountdown - (1 * (input.softDrop * (20 * (UPDATES_A_SECOND / 60))));
            }


            if ((!prevInput.rotLeft) && (input.rotLeft))
                board.tryRotate(currentPiece, TurnDirection::Left);
            else if ((!prevInput.rotRight) && (input.rotRight))
                board.tryRotate(currentPiece, TurnDirection::Right);
        }
    }
}

void Game::render(RenderWindow& window) {

}

Game::~Game()
{

}