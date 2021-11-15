#pragma once

#include "PieceDefs.hpp"
#include "../../../../Platform/SDL2/headers/RenderWindow.hpp"
#include "../../../../Platform/SDL2/headers/Game.hpp"
#include <vector>

const auto half(int i) {
    return i / 2;
}
const auto getRandPiece() {
    

    switch (rand() % 7)
    {
    case 0:
        return PieceType::S;
        break;
    case 1:
        return PieceType::Z;
        break;
    case 2:
        return PieceType::J;
        break;
    case 3:
        return PieceType::L;
        break;
    case 4:
        return PieceType::T;
        break;
    case 5:
        return PieceType::O;
        break;
    case 6:
        return PieceType::I;
        break;
    default:
        return PieceType::T;
        break;
    }

};

const int BOARDWIDTH = 10;
const int BOARDHEIGHT = 20;


class Board;
class Piece {
public:
    Piece(PieceType kind, int_fast8_t x = 4 - half(PIECEWIDTH), int_fast8_t y = 19 - half(PIECEHEIGHT), RotationDirection spin = RotationDirection::North) {
        this->kind = kind;
        setX(x); setY(y);
        this->spin = spin;

        //populate local piece definition
        for (size_t w = 0; w < PIECEWIDTH; w++)
        {
            for (size_t h = 0; h < PIECEHEIGHT; h++)
            {
                piecedef[w][h] = PieceDefinition[PieceTypeToColorType(kind)][w][h];
            }
        }
         //match up the spin direction of the local piece definition with what is given by the params
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
                piecedef[x][y] = piecedef[y][(size_t)PIECEWIDTHANDHEIGHT - 1 - x];

                // Move values from bottom to right
                piecedef[y][(size_t)PIECEWIDTHANDHEIGHT - 1 - x]
                    = piecedef[(size_t)PIECEWIDTHANDHEIGHT - 1 - x][(size_t)PIECEWIDTHANDHEIGHT - 1 - y];

                // Move values from left to bottom
                piecedef[(size_t)PIECEWIDTHANDHEIGHT - 1 - x][(size_t)PIECEWIDTHANDHEIGHT - 1 - y]
                    = piecedef[(size_t)PIECEWIDTHANDHEIGHT - 1 - y][x];

                // Assign temp to left
                piecedef[(size_t)PIECEWIDTHANDHEIGHT - 1 - y][x] = temp;
            }
        }
    }

    inline void setX(int_fast8_t setter) {
        x = setter;
        realX = setter + half(PIECEWIDTH);
    }
    inline void setY(int_fast8_t setter) {
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
        while (trySoftDrop(piece))
            piece.setY((piece.y - 1));
        return;
    }

    bool trySoftDrop(Piece &piece) {
        piece.setY((piece.x-1));
        if (isCollide(piece)) {
            piece.setY((piece.x+1)); // if it collided, go back up where it should be safe
            return true;
        }
        return false;
    }

    bool tryRotateLeft(Piece &piece) {
        if (piece.kind == PieceType::O)
            return true;
        // rotate the piece definition left first
        // this is to test if we can even rotate it in the first place
        // need to rotate it back if fails 
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
        return true;
    }


    bool tryRotate(Piece &piece, TurnDirection direction) {
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

    void setPiece(const Piece &piece) {
        for (int h = piece.y, PieceW = PIECEHEIGHT - 1; h < PIECEHEIGHT + piece.y; h++, PieceW--)// subtract the width cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int w = piece.x, PieceH = 0; w < PIECEWIDTH + piece.x; w++, PieceH++)
            {
                if ((((0 <= h) && (h < BOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    if(piece.piecedef[PieceW][PieceH] != empty)
                        board.at(w).at(h) = piece.piecedef[PieceW][PieceH];
                }
            }
        }
    }

    bool isCollide(const Piece &piece) {
        for (int w = piece.x; w < PIECEWIDTH + piece.x; w++)// subtract the height cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int h = piece.y; h < PIECEHEIGHT + piece.y; h++)
            {
                    int x = w - piece.x;
                    int y = 4 - h + piece.y;
                if ((((0 <= h) && (h < BOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    ColorType pieceBlock = piece.piecedef[y][x];
                    if (pieceBlock != empty) // is the cell empty in the piece matrix is empty

                        if (board.at(w).at(h) != empty) // is the cell in the board matrix empty
                            return true;
                }
                if (h < 0) // can be above, but not below the board
                {
                    ColorType pieceBlock = piece.piecedef[y][x];
                    if (pieceBlock != empty)
                        return true;
                }
                else if ((w < 0) || (w >= BOARDWIDTH)) // cant be out of bounds on either direction
                {
                    ColorType pieceBlock = piece.piecedef[y][x];
                    if (pieceBlock != empty)
                        return true;
                }
            }
        }
        return false;
    }

    constexpr const char colorTypeToString(const ColorType bruh) {
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

    void gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput);
    void render(RenderWindow& window);
    void Init(RenderWindow& window) {
        this->background.Init("Asset/Sprites/exampleAssets/TetrisBackground.png", window); //1080p background
        this->matrix.Init("Asset/Sprites/Tetris_images/Matrix.png", window); // original size is 224 by 299
        this->pieces.Init("Asset/Sprites/exampleAssets/TetrisPieces.png", window);
        //this->matrixBackground.Init("Asset/Sprites/exampleAssets/matrixBackground", window); //need this later
        this->background.sprite = { 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT };
        this->matrix.sprite = {
            ((DEFAULT_SCREEN_WIDTH - (224 * 3)) / 3) - 50 ,
            ((DEFAULT_SCREEN_HEIGHT - (299 * 3)) / 3) - 100,
            (224 * 4),
            (299 * 4)
        }; // first pixel on the matrix should be 50, 34
        pieces.textureRegion = {0, 0, 16, 16};
        pieces.sprite = {0,0,24,24};
    }
private:
    Piece currentPiece{ PieceType::S };
    std::vector<Piece> queue{};
    Board board;

    autoTexture background;
    autoTexture matrix;
    autoTexture pieces;
    autoTexture matrixBackground;
};

Game::Game()
{
    printf("example initialized");
    //temp pieces
    queue.reserve(7);
    queue.emplace_back(Piece(PieceType::S));
    queue.emplace_back(Piece(PieceType::Z));
    queue.emplace_back(Piece(PieceType::T));
    queue.emplace_back(Piece(PieceType::L));
    queue.emplace_back(Piece(PieceType::T));
    queue.emplace_back(Piece(PieceType::O));
    queue.emplace_back(Piece(PieceType::I));

}

const static auto softdropCountdownMAX = (4096 * (1000 /60)); // 4096 cause thats what ppt uses according to fug
static auto softdropCountdown = softdropCountdownMAX;

const static uint16_t pieceSpawnDelayMAX = UPDATES_A_SECOND;
static int32_t pieceSpawnDelay = pieceSpawnDelayMAX;

void Game::gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) {
    

    if (currentPiece.kind != PieceType::empty) // we have a piece!
    {
        if ((input.hardDrop) && !(prevInput.hardDrop))
        {
            board.sonicDrop(currentPiece);
            board.setPiece(currentPiece);
            currentPiece.kind = PieceType::empty;
        }
        if ((input.left) && !(prevInput.left))
        {
            currentPiece.setX(currentPiece.x - 1);
            if (board.isCollide(currentPiece))
                currentPiece.setX(currentPiece.x + 1);
        }
        if ((input.right) && !(prevInput.right))
        {
            currentPiece.setX(currentPiece.x + 1);
            if (board.isCollide(currentPiece))
                currentPiece.setX(currentPiece.x - 1);
        }
        else {


            if (softdropCountdown <= 0)
            {
                //softdrop pls
                if (!board.trySoftDrop(currentPiece)) {
                    board.setPiece(currentPiece); 
                    currentPiece.kind = PieceType::empty;
                }
                else 
                    currentPiece.setY(currentPiece.y - 1);

                softdropCountdown = softdropCountdownMAX;
            }
            else {
                // 20 is another number ppt uses according to fug, and the 60 is for the updates a second ppt uses in their game
                if (input.softDrop)
                    softdropCountdown -= (20 * (UPDATES_A_SECOND / 60));
                else
                    softdropCountdown-= (UPDATES_A_SECOND / 60);
            }


            if ((!prevInput.rotLeft) && (input.rotLeft))
                board.tryRotate(currentPiece, TurnDirection::Left);
            else if ((!prevInput.rotRight) && (input.rotRight))
                board.tryRotate(currentPiece, TurnDirection::Right);

        }
    } else if (pieceSpawnDelay <= 0) { //guarenteed no piece
        pieceSpawnDelay = pieceSpawnDelayMAX;
        currentPiece = queue.at(0);
        queue.erase(queue.begin()); 
        queue.emplace_back(Piece(getRandPiece()));
    } else 
        pieceSpawnDelay--;
    if (input.menuSelect)
        ; // delete game
}

void Game::render(RenderWindow& window) {
    window.render(background);
    window.render(matrix);
    const uint16_t width_offset = (((DEFAULT_SCREEN_WIDTH - (224 * 3)) / 3) - 50) + (50 * 4) - 1;
    const uint16_t height_offset = (((DEFAULT_SCREEN_HEIGHT - (299 * 3)) / 3) - 100) + (34 * 4) - 1; 
    // the minus ones because otherwise https://cdn.discordapp.com/attachments/802969309260677120/909250930506080326/unknown.png
    for (int_fast8_t height = BOARDHEIGHT - 1; height >= 0; height--)
    {
        for (int_fast8_t width = 0; width < BOARDWIDTH; width++)
        {
            auto helper = [&]() {
                

                pieces.sprite.x = width_offset + (width * (24 * 2));
                pieces.sprite.w = 16 * 3;
                pieces.sprite.y = height_offset + ((BOARDHEIGHT- height-1) * (24 * 2));
                pieces.sprite.h = 16 * 3;
            };
            auto drawPiece = [&](ColorType block) {
                switch (block)
                {
                case empty:
                    pieces.textureRegion.x = 16;
                    helper();
                    break;
                case Z:
                    pieces.textureRegion.x = 32;
                    break;
                    helper();
                case L:
                    pieces.textureRegion.x = 48;
                    helper();
                    break;
                case O:
                    pieces.textureRegion.x = 64;
                    helper();
                    break;
                case S:
                    pieces.textureRegion.x = 80;
                    helper();
                    break;
                case I:
                    pieces.textureRegion.x = 96;
                    helper();
                    break;
                case J:
                    pieces.textureRegion.x = 112;
                    helper();
                    break;
                case T:
                    pieces.textureRegion.x = 128;
                    helper();
                    break;
                case line_clear:
                    pieces.textureRegion.x = 144;
                    helper();
                    break;
                default:
                    break;
                }
            };

            if (((currentPiece.x <= width) && (width <= (currentPiece.x + PIECEWIDTH - 1))) && ((currentPiece.y <= height) && (height <= (currentPiece.y + PIECEHEIGHT - 1))))
            {
                ColorType block = currentPiece.piecedef[4 - height + currentPiece.y][width - currentPiece.x];
                if (block != empty)
                    drawPiece(block);
                else
                    drawPiece(board.board[width][height]);

            }
            else
                drawPiece(board.board[width][height]);


            window.render(pieces);
        }

    }
}

Game::~Game()
{

}