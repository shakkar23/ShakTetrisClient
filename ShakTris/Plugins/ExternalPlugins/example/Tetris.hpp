#pragma once

#include "PieceDefs.hpp"
#include "../../../../Platform/SDL2/headers/RenderWindow.hpp"
#include "../../../../Platform/SDL2/headers/Game.hpp"
#include "combo_table.hpp"
#include "damageTable.hpp"
#include "ppt.h"
#include <vector>
#include <span>
#include <cassert>
#include <SDL_ttf.h>


constexpr int half(int i) {
    return i / 2;
}
const auto getRandPiece() {
    

    switch (pptRand())
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

constexpr auto BOARDWIDTH = 10;
constexpr auto VISUALBOARDHEIGHT = 20;
constexpr auto LOGICALBOARDHEIGHT = 40;

class Board;
class Piece {
public:
    Piece(PieceType kind, int_fast8_t x = 4 - half(PIECEWIDTH), int_fast8_t y = VISUALBOARDHEIGHT - (PIECEHEIGHT) + 1, RotationDirection spin = RotationDirection::North) {
        //force the RNG to throw away its previous bag, and make a new one
        
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
            rotatePieceMatrixLeft(); rotatePieceMatrixLeft(); rotatePieceMatrixLeft();
            break;
        case South:
            rotatePieceMatrixLeft(); rotatePieceMatrixLeft();
            break;
        case West:
            rotatePieceMatrixLeft();
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
    void rotatePieceMatrixLeft()
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

    void setX(int_fast8_t setter) {
        x = setter;
        realX = setter + half(PIECEWIDTH);
    }
    void setY(int_fast8_t setter) {
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
        clear();
    }
    void makeBoardGarbage() {
        for (auto& lines : board)
            for (auto& mino : lines)
                if(mino != ColorType::empty)    
                    mino = ColorType::line_clear;
    }
    void clear() {
        for (auto& width : board)
        {
            for (auto& cell : width)
            {
                cell = empty;
            }
        }
    }
    int clearLines() {
        int linesCleared{};
        for (size_t h = 0; h < LOGICALBOARDHEIGHT; h++)
        {
            for (size_t w = 0; w < BOARDWIDTH; w++)
            {
                if (board.at(w).at(h) == empty)
                    break;
                if (w == BOARDWIDTH - 1) {
                    clearLine(h);
                    linesCleared++;
                    h--;
                }
            }
        }
        return linesCleared;
    };
    void clearLine(uint_fast8_t whichLine) {
        if (whichLine >= LOGICALBOARDHEIGHT)
            whichLine = LOGICALBOARDHEIGHT - 1;
        for (size_t i = 0; i < BOARDWIDTH; i++)
        {
            board.at(i).at(whichLine) = empty;
        }
        for (size_t w = 0; w < BOARDWIDTH; w++)
        {
            for (size_t h = whichLine; h < LOGICALBOARDHEIGHT; h++)
            {
                if (h == (LOGICALBOARDHEIGHT - 1))
                {
                    board.at(w).at(h) = empty;
                    break;
                }
                else
                    board.at(w).at(h) = board.at(w).at(h + 1);
            }

        }
    }
    void sonicDrop(Piece& piece) {
        while (trySoftDrop(piece));
    }

    bool trySoftDrop(Piece &piece) {
        piece.setY(piece.y - 1);
        if (isCollide(piece)) {
            piece.setY(piece.y+1); // if it collided, go back up where it should be safe
            return false;
        }
        return true;
    }

    [[deprecated]] bool tryRotateLeft(Piece &piece) {
        if (piece.kind == PieceType::O)
            return true;
        // rotate the piece definition left first
        // this is to test if we can even rotate it in the first place
        // need to rotate it back if fails 
        piece.rotatePieceMatrixLeft();
        piece.rotatePieceMatrixLeft();
        piece.rotatePieceMatrixLeft();
        for (int h = piece.y, PieceW = PIECEHEIGHT - 1; h < PIECEHEIGHT + piece.y; h++, PieceW--)// subtract the width cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int w = piece.x, PieceH = 0; w < PIECEWIDTH + piece.x; w++, PieceH++)
            {
                if ((((0 <= h) && (h < VISUALBOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    if ((board.at(w).at(h) != ColorType::empty) && (piece.piecedef[PieceW][PieceH] != ColorType::empty))
                        continue;
                    else {
                        piece.rotatePieceMatrixLeft();
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void setPiece(const Piece &piece) {
        new Shakkar::autoAudio("Asset/Sounds/Sound.wav", (128/5));
        for (int h = piece.y, PieceW = PIECEHEIGHT - 1; h < PIECEHEIGHT + piece.y; h++, PieceW--)// subtract the width cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int w = piece.x, PieceH = 0; w < PIECEWIDTH + piece.x; w++, PieceH++)
            {
                if ((((0 <= h) && (h < LOGICALBOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    if(piece.piecedef[PieceW][PieceH] != empty)
                        board.at(w).at(h) = piece.piecedef[PieceW][PieceH];
                }
            }
        }
    }

    bool isCollide(const Piece &piece) {
        for (int w = piece.x; w < (PIECEWIDTH + piece.x); w++)// subtract the height cause yes, it makes adding go up, due to the nautre of how to display arrays visually
        {
            for (int h = piece.y; h < (PIECEHEIGHT + piece.y); h++)
            {
                    int x = w - piece.x;
                    int y = 4 - h + piece.y;
                if ((((0 <= h) && (h < LOGICALBOARDHEIGHT))) && (((0 <= w) && (w < BOARDWIDTH)))) //if inbounds of board
                {
                    if (piece.piecedef[y][x] != empty) // is the cell empty in the piece matrix is empty
                        if (board.at(w).at(h) != empty) // is the cell in the board matrix empty
                            return true;
                }

                if ((w < 0) || (w >= BOARDWIDTH)) // cant be out of bounds on either direction
                {
                    if (piece.piecedef[y][x] != empty)
                        return true;
                }

                if (h < 0) // can be above, but not below the board
                {
                    if (piece.piecedef[y][x] != empty)
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
        for (int_fast8_t h = VISUALBOARDHEIGHT - 1; h >= 0; h--)
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
        for (int_fast8_t h = VISUALBOARDHEIGHT - 1; h >= 0; h--)
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
    std::array< std::array<ColorType, LOGICALBOARDHEIGHT>, BOARDWIDTH> board{};
};
class Game
{
public:

    Game();
    ~Game();

    void gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput);
    void render(RenderWindow& window);

    void Init(RenderWindow& window) {
        //forceReRollBag();
        hold = Piece(PieceType::empty);
        queue.clear();
        queue.reserve(7);
        forceReRollBag();
        currentPiece = Piece(getRandPiece());
        for (size_t i = 0; i < 7; i++)
            queue.emplace_back(Piece(getRandPiece()));
        this->background.Init("Asset/Sprites/exampleAssets/TetrisBackground.png", window); //1080p background
        this->matrix.Init("Asset/Sprites/Tetris_images/Matrix.png", window); // original size is 224 by 299
        this->pieces.Init("Asset/Sprites/exampleAssets/TetrisPieces.png", window);
        this->ghostPieces.Init("Asset/Sprites/exampleAssets/TetrisPieces.png", window);
        Uint8 a = 100;
        this->ghostPieces.modifyTex(a);
        if (!font)
            this->font = TTF_OpenFont("Asset/Sprites/exampleAssets/F77MinecraftReg.ttf", 36);
        //this->matrixBackground.Init("Asset/Sprites/exampleAssets/matrixBackground", window); //need this later
        timeWhenInit = SDL_GetPerformanceCounter();
        piecesPlaced = 0;
        softdropCountdown = softdropCountdownMAX;
        pieceSpawnDelay = pieceSpawnDelayMAX;
        lockDelayIncrementer = 0;
        isDie = false;
        checkForLineClear = false;
        alreadyHeld = false;
        currentCombo = 0;
        b2b = false;
        numLinesCleared = 0;
        numDamageSent = 0;
        Tspinned = false;

        this->background.sprite = { 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT };
        this->matrix.sprite = {
            matrixX ,
            matrixY,
            (224 * 4),
            (299 * 4)
        }; // first pixel on the matrix should be 50, 34
        pieces.textureRegion = { 0, 0, 16, 16 };
        pieces.sprite = { 0,0,24,24 };
        ghostPieces.textureRegion = { 0, 0, 16, 16 };
        ghostPieces.sprite = { 0,0,24,24 };
    }
    void reload() {

        board.clear();
    }
private:
    void tryMovePiece(MoveDirection direction, bool JustPressed) {

        int offset{};
        if (direction == MoveDirection::Left)
            offset = -1;
        else
            offset = 1;

        if (JustPressed) {
            dasIterator = 0;
            arrIterator = 0;
            currentPiece.setX(currentPiece.x + offset);
            if (board.isCollide(currentPiece))
            {
                currentPiece.setX(currentPiece.x - offset); // failed, go back
                return;
            }
            else
                return;

        }

        if (dasIterator >= dasSetting) {
            // success! now try to das
            if (arrIterator >= arrSetting)
            {
                for (; arrIterator >= arrSetting; arrIterator -= arrSetting)
                {
                    currentPiece.setX(currentPiece.x + offset);
                    if (board.isCollide(currentPiece))
                    {
                        currentPiece.setX(currentPiece.x - offset); // failed, go back
                        return;
                    }
                }
            }
            else
                arrIterator += (1000 / UPDATES_A_SECOND);
        }
        else
            dasIterator += (1000 / UPDATES_A_SECOND);

        return;
    }
    /*/bool isEmpty(int x, int y, Board& board) {
        if ((((0 <= y) && (y < LOGICALBOARDHEIGHT))) && (((0 <= x) && (x < BOARDWIDTH)))) //if inbounds of board
        {
            //if (piece.piecedef[y][x] != empty) // is the cell empty in the piece matrix is empty
            if (board.board.at(x).at(y) != empty) // is the cell in the board matrix empty
                return true;
            else
                return false;
        }

        if ((x < 0) || (x >= BOARDWIDTH)) // cant be out of bounds on either direction
        {
            return true;
        }

        if (y < 0) // can be above, but not below the board
        {
            return true;
        }
        return false;
    }*/
    bool tryRotate(Piece& piece, TurnDirection direction) {
        auto incrRot = [&](RotationDirection& spin) {
            switch (spin)
            {
            case North:
                spin = East;
                break;
            case East:
                spin = South;
                break;
            case South:
                spin = West;
                break;
            case West:
                spin = North;
                break;
            default:
                break;
            }
        };
        auto TspinDetection = [](Piece& piece, Board& board, bool& Tspinned) {
                auto isEmpty = [](int x, int y, Board& board) {
                    if ((((0 <= y) && (y < LOGICALBOARDHEIGHT))) && (((0 <= x) && (x < BOARDWIDTH)))) //if inbounds of board
                    {
                        //if (piece.piecedef[y][x] != empty) // is the cell empty in the piece matrix is empty
                        if (board.board.at(x).at(y) != empty) // is the cell in the board matrix empty
                            return true;
                        else
                            return false;
                    }

                    if ((x < 0) || (x >= BOARDWIDTH)) // cant be out of bounds on either direction
                    {
                        return true;
                    }

                    if (y < 0) // can be above, but not below the board
                    {
                        return true;
                    }
                    return false;
                };
            if (piece.kind == PieceType::T) {
                bool topright(isEmpty(piece.realX + 1, piece.realY + 1, board));
                bool topleft(isEmpty(piece.realX - 1, piece.realY + 1, board));
                bool bottomright(isEmpty(piece.realX + 1, piece.realY - 1, board));
                bool bottomleft(isEmpty(piece.realX - 1, piece.realY - 1, board));
                uint8_t corners = topright + topleft + bottomright + bottomleft;
                if (corners >= 3)
                    Tspinned = true;
                else
                    Tspinned = false;
            }
        };
        // temporary x and y to know their initial location
        const int_fast8_t x = piece.x;
        const int_fast8_t y = piece.y;
        if (direction == Right)
        {
            piece.rotatePieceMatrixLeft();
            piece.rotatePieceMatrixLeft();
            piece.rotatePieceMatrixLeft();
        }
        else if (direction == Left)
        {
            piece.rotatePieceMatrixLeft();
        }
        else if (direction == oneEighty)
        {
            piece.rotatePieceMatrixLeft();
            piece.rotatePieceMatrixLeft();
        }

        // spinclockwise should be a bool, but it can also be 2 as in rotating twice
        // in one frame aka 180 spin
        if (direction != TurnDirection::oneEighty) {
            RotationDirection nextDir = piece.spin;
            if (direction == Right)
                incrRot(nextDir);
            else if (direction == Left)
            {
                incrRot(nextDir); incrRot(nextDir); incrRot(nextDir);
            }

            auto* offsetData = &JLSTZPieceOffsetData[piece.spin];
            auto* nextOffset = &JLSTZPieceOffsetData[nextDir];
            if (piece.kind == PieceType::I) {
                offsetData = &IPieceOffsetData[piece.spin];
                nextOffset = &IPieceOffsetData[nextDir];
            }
            else if (piece.kind == PieceType::O)
            {
                offsetData = &OPieceOffsetData[piece.spin];
                nextOffset = &OPieceOffsetData[nextDir];
            }

            for (int i = 0; i < kicks; ++i) {

                piece.setX(x + (*offsetData)[i][0] - (*nextOffset)[i][0]);
                piece.setY(y + (*offsetData)[i][1] - (*nextOffset)[i][1]);

                if (!board.isCollide(piece)) {
                    piece.spin = nextDir;
                    TspinDetection(piece, board, Tspinned);
                    return true;
                }
            }
            piece.setX(x); piece.setY(y);
        }
        else 
        {
            RotationDirection nextDir = piece.spin;
            incrRot(nextDir); incrRot(nextDir);

            auto *kickdata = &wallkick180data[piece.spin];
            auto *nextkickdata = &wallkick180data[nextDir];
            if (piece.kind == PieceType::I)
            {
                kickdata = &Iwallkick180data[piece.spin];
                nextkickdata = &wallkick180data[nextDir];
            }
            
            for (int i = 0; i < 12; ++i) {
                auto kickx = (*kickdata)[i][0];
                auto kicky = (*kickdata)[i][1];
                if (piece.kind == PieceType::I)
                {
                    std::swap(kickx, kicky);
                    kickx += OPieceOffsetData[piece.spin][i][0];
                    kicky += OPieceOffsetData[piece.spin][i][1];
                }
                else {
                    kicky = -kicky;
                }
                piece.setX(x + kickx);
                piece.setY(y + kicky);

                if (!board.isCollide(piece)) {
                    incrRot(piece.spin); incrRot(piece.spin);
                    TspinDetection(piece, board, Tspinned);
                    return true;
                }
            }
            piece.setX(x); piece.setY(y);
        }

        //rotate the matrix back if nothing worked
        if (direction == Right) {
            piece.rotatePieceMatrixLeft();
        }
        else if (direction == Left)
        {
            piece.rotatePieceMatrixLeft();
            piece.rotatePieceMatrixLeft();
            piece.rotatePieceMatrixLeft();
        }
        else if (direction == oneEighty)
        {
            piece.rotatePieceMatrixLeft();
            piece.rotatePieceMatrixLeft();
        }
        return false;
    }

    const int16_t matrixXPos = (((DEFAULT_SCREEN_WIDTH - (224 * 3)) / 3) - 50);
    const int16_t matrixYPos = (((DEFAULT_SCREEN_HEIGHT - (299 * 3)) / 3) - 100);
    int16_t matrixX = matrixXPos;
    int16_t matrixY = matrixYPos;

    const uint16_t dasSetting = 80; // these are in miliseconds
    const uint16_t arrSetting = 0;
    uint16_t dasIterator = 0;
    uint16_t arrIterator = 0;
    Piece hold{ PieceType::empty };
    Piece currentPiece{ PieceType::empty };
    std::vector<Piece> queue{};
    Board board;
    autoTexture background;
    autoTexture matrix;
    autoTexture pieces;
    autoTexture ghostPieces;
    autoTexture matrixBackground;
    TTF_Font* font{};
    Uint64 timeWhenInit{};
    int piecesPlaced{};
    const int softdropCountdownMAX = (UPDATES_A_SECOND);
    int softdropCountdown = softdropCountdownMAX;
    const uint8_t pieceSpawnDelayMAX = 0;
    int32_t pieceSpawnDelay = pieceSpawnDelayMAX;
    const uint_fast16_t lockDelayMAX = (UPDATES_A_SECOND);
    uint16_t lockDelayIncrementer{};
    uint16_t numLinesCleared{};
    uint16_t numDamageSent{};
    int8_t currentCombo{};
    bool placedPiece{};
    bool isDie{};
    bool checkForLineClear{};
    bool alreadyHeld{};
    bool b2b{};
    bool leftPressedMostRecent{};
    bool rightPressedMostRecent{};
    bool Tspinned{};

};

Game::Game()
{
    
}

void Game::gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput) {

    if (justPressed(prevInput.left, input.left)) {
        leftPressedMostRecent = true;
        rightPressedMostRecent = false;
    }
    else if(justPressed(prevInput.right, input.right)) {
        rightPressedMostRecent = true;
        leftPressedMostRecent = false;
    }

    bool leftState{};
    bool rightState{};

    leftState = (rightPressedMostRecent && input.right) ? false : input.left;
    rightState = (leftPressedMostRecent && input.left) ? false : input.right;

    if (checkForLineClear) {
        int linesCleared = board.clearLines();
        if (linesCleared == 0)
            currentCombo = 0;
        auto tmp1 = std::clamp(int(linesCleared), 0, DAMAGETABLESIZE - 1);
        auto tmp2 = std::clamp(int(currentCombo), 0, COMBOTABLESIZE - 1);
        if (Tspinned) {
            numDamageSent += (linesCleared * 2) + comboTable[tmp2];
        }
        else 
            numDamageSent += damageTable[tmp1] + comboTable[tmp2];

        if (linesCleared > 0) {
            currentCombo++;
            this->numLinesCleared += linesCleared;
        }
        if ((linesCleared == 4) || Tspinned)
        {
            if (b2b) {
                numDamageSent += 2;
            }
            b2b = true;
            Tspinned = false;
        }
        else if (linesCleared > 0)    
            b2b = false;
        checkForLineClear = false;
    }


    if ((currentPiece.kind != PieceType::empty) && !isDie) // we have a piece!
    {
        if (justPressed(prevInput.hardDrop, input.hardDrop))
        {
            board.sonicDrop(currentPiece);
            board.setPiece(currentPiece);
            currentPiece.kind = PieceType::empty;
            checkForLineClear = true;
            lockDelayIncrementer = 0;
            alreadyHeld = false;
            placedPiece = true;
        }

        if (leftState)
        {
            tryMovePiece(MoveDirection::Left, !prevInput.left);
        }
        else if (rightState)
        {
            tryMovePiece(MoveDirection::Right, !prevInput.right);
        }

        {
            if (softdropCountdown <= 0)
            {
                //softdrop pls
                if (!board.trySoftDrop(currentPiece)) {
                    //failed, we are on the ground
                    if (lockDelayIncrementer >= lockDelayMAX)
                    {
                        board.setPiece(currentPiece);
                        currentPiece.kind = PieceType::empty;
                        checkForLineClear = true;
                        lockDelayIncrementer = 0;
                        alreadyHeld = false;
                        placedPiece = true;
                    }
                    else 
                        lockDelayIncrementer++;
                   
                }else 
                    softdropCountdown = softdropCountdownMAX;
            }
            else {
                
                if (input.softDrop)
                    softdropCountdown -= 40;
                else
                    softdropCountdown -= 1;
            }

            if (justPressed(prevInput.rotLeft, input.rotLeft))
                tryRotate(currentPiece, TurnDirection::Left);

            else if (justPressed(prevInput.rotRight, input.rotRight))
                tryRotate(currentPiece, TurnDirection::Right);

            else if (justPressed(prevInput.rot180, input.rot180))
                tryRotate(currentPiece, TurnDirection::oneEighty);

            if (prevInput.sonicDrop)
                board.sonicDrop(currentPiece);
            // hold logic
            if (justPressed(prevInput.hold, input.hold))
            {
                if (!alreadyHeld) {
                    std::swap(currentPiece, hold);
                    currentPiece.setX(4 - half(PIECEWIDTH));
                    currentPiece.setY(VISUALBOARDHEIGHT - (PIECEHEIGHT)+1);

                    switch (currentPiece.spin)
                    {
                    case North:
                        break;
                    case East:
                        currentPiece.rotatePieceMatrixLeft();
                        break;
                    case South:
                        currentPiece.rotatePieceMatrixLeft(); currentPiece.rotatePieceMatrixLeft();
                        break;
                    case West:
                        currentPiece.rotatePieceMatrixLeft(); currentPiece.rotatePieceMatrixLeft(); currentPiece.rotatePieceMatrixLeft();
                        break;
                    default:
                        break;
                    }
                    currentPiece.spin = North;

                    switch (hold.spin)
                    {
                    case North:
                        break;
                    case East:
                        hold.rotatePieceMatrixLeft();
                        break;
                    case South:
                        hold.rotatePieceMatrixLeft(); hold.rotatePieceMatrixLeft();
                        break;
                    case West:
                        hold.rotatePieceMatrixLeft(); hold.rotatePieceMatrixLeft(); hold.rotatePieceMatrixLeft();
                        break;
                    default:
                        break;
                    }
                    hold.spin = North;
                    Tspinned = false;
                    alreadyHeld = true;

                    if (board.isCollide(currentPiece)) {
                        currentPiece.setY(currentPiece.y + 1);
                        if (board.isCollide(currentPiece)) {
                            currentPiece.setY(currentPiece.y - 1);
                            board.makeBoardGarbage();
                            isDie = true;
                        }
                    }
                }
            }


        }
    } 
    else if ((pieceSpawnDelay <= 0) && !isDie) { //guarenteed no piece

        pieceSpawnDelay = pieceSpawnDelayMAX;
        softdropCountdown = softdropCountdownMAX;

        currentPiece = queue.at(0);
        queue.erase(queue.begin()); 
        queue.emplace_back(Piece(getRandPiece()));

        if (board.isCollide(currentPiece)) {
            currentPiece.setY(currentPiece.y + 1);
            if (board.isCollide(currentPiece)) {
                currentPiece.setY(currentPiece.y - 1);
                board.makeBoardGarbage();
                isDie = true;
            }
        }
        leftState = false;
        rightState = false;
        checkForLineClear = false;

    } else 
        pieceSpawnDelay--;
}


void Game::render(RenderWindow& window) {
    window.render(background);
    
    matrix.sprite.x = matrixX ;
    matrix.sprite.y = matrixY;

    window.render(matrix);

    const int16_t board_width_offset = matrixX + (50 * 4) - 1;
    const int16_t board_height_offset = matrixY + (34 * 4) - 1;

    Piece ghost(currentPiece.kind, currentPiece.x, currentPiece.y, currentPiece.spin);
    if (ghost.kind != PieceType::empty)
        board.sonicDrop(ghost);

    // render the board
    // the minus ones because otherwise https://cdn.discordapp.com/attachments/802969309260677120/909250930506080326/unknown.png
    for (int_fast8_t height = VISUALBOARDHEIGHT - 1; height >= 0; height--)
    {
        for (int_fast8_t width = 0; width < BOARDWIDTH; width++)
        {
            auto helper = [&](autoTexture& minos) {
                minos.sprite.x = board_width_offset + (width * (24 * 2));
                minos.sprite.w = 16 * 3;
                minos.sprite.y = board_height_offset + ((VISUALBOARDHEIGHT - height - 1) * (24 * 2));
                minos.sprite.h = 16 * 3;
            };
            auto drawPiece = [&](ColorType block, autoTexture& minos) {
                switch (block)
                {
                case empty:
                    minos.textureRegion.x = 16;
                    helper(minos);
                    break;
                case Z:
                    minos.textureRegion.x = 32;
                    helper(minos);
                    break;
                case L:
                    minos.textureRegion.x = 48;
                    helper(minos);
                    break;
                case O:
                    minos.textureRegion.x = 64;
                    helper(minos);
                    break;
                case S:
                    minos.textureRegion.x = 80;
                    helper(minos);
                    break;
                case I:
                    minos.textureRegion.x = 96;
                    helper(minos);
                    break;
                case J:
                    minos.textureRegion.x = 112;
                    helper(minos);
                    break;
                case T:
                    minos.textureRegion.x = 128;
                    helper(minos);
                    break;
                case line_clear:
                    minos.textureRegion.x = 144;
                    helper(minos);
                    break;
                default:
                    break;
                }
            };
            if (((currentPiece.x <= width) && (width <= (currentPiece.x + PIECEWIDTH - 1))) && ((currentPiece.y <= height) && (height <= (currentPiece.y + PIECEHEIGHT - 1))) &&
                (currentPiece.piecedef[4 - height + currentPiece.y][width - currentPiece.x] != empty) && currentPiece.kind != PieceType::empty)
            {
                drawPiece(PieceTypeToColorType(currentPiece.kind), pieces);
                window.render(pieces);

            }
            else if (((ghost.x <= width) && (width <= (ghost.x + PIECEWIDTH - 1))) && ((ghost.y <= height) && (height <= (ghost.y + PIECEHEIGHT - 1))) &&
                (ghost.piecedef[4 - height + ghost.y][width - ghost.x] != empty) && ghost.kind != PieceType::empty)
            {
                drawPiece(PieceTypeToColorType(ghost.kind), ghostPieces);
                window.render(ghostPieces);
            }
            else {
                drawPiece(board.board[width][height], pieces);
                window.render(pieces);

            }
        }
    }

    int16_t queue_width_offset = board_width_offset + (122 * 4) - 1 - 1;
    int16_t queue_height_offset = board_height_offset;

    //render queue 5 pieces to be seen, each with its own matrix of a 5x5 view
    for (size_t q = 0; q < 5; q++)
    {
        for (int y = PIECEHEIGHT - 1; y >= 0; y--)
            //for (int y = 0; y < PIECEHEIGHT; y++)
        {
            for (int x = 0; x < PIECEWIDTH; x++)
                //for (int x = PIECEWIDTH -1; x >= 0; x--)
            {
                auto helper = [&](autoTexture& minos) {
                    minos.sprite.x = queue_width_offset + (x * (16 * 2));
                    minos.sprite.w = 16 * 2;
                    minos.sprite.y = queue_height_offset + ((y) * (16 * 2));
                    minos.sprite.h = 16 * 2;
                };
                auto drawPiece = [&](ColorType block, autoTexture& minos) {
                    switch (block)
                    {
                    case empty:
                        minos.textureRegion.x = 16;
                        helper(minos);
                        break;
                    case Z:
                        minos.textureRegion.x = 32;
                        helper(minos);
                        break;
                    case L:
                        minos.textureRegion.x = 48;
                        helper(minos);
                        break;
                    case O:
                        minos.textureRegion.x = 64;
                        helper(minos);
                        break;
                    case S:
                        minos.textureRegion.x = 80;
                        helper(minos);
                        break;
                    case I:
                        minos.textureRegion.x = 96;
                        helper(minos);
                        break;
                    case J:
                        minos.textureRegion.x = 112;
                        helper(minos);
                        break;
                    case T:
                        minos.textureRegion.x = 128;
                        helper(minos);
                        break;
                    case line_clear:
                        minos.textureRegion.x = 144;
                        helper(minos);
                        break;
                    default:
                        break;
                    }
                };
                drawPiece(queue[q].piecedef[y][x], pieces);
                window.render(pieces);
            }
        }
        queue_height_offset += (2 * 4);
        queue_height_offset += (PIECEHEIGHT * 16 * 2);
    }


    const int16_t hold_width_offset = board_width_offset - (42 * 4);
    const int16_t hold_height_offset = board_height_offset;

    //render the holds
    for (int h = 0; h < 1; h++)
    {
        for (int y = PIECEHEIGHT - 1; y >= 0; y--)
            //for (int y = 0; y < PIECEHEIGHT; y++)
        {
            for (int x = 0; x < PIECEWIDTH; x++)
                //for (int x = PIECEWIDTH -1; x >= 0; x--)
            {
                auto helper = [&](autoTexture& minos) {
                    minos.sprite.x = hold_width_offset + (x * (16 * 2));
                    minos.sprite.w = 16 * 2;
                    minos.sprite.y = hold_height_offset + ((y) * (16 * 2));
                    minos.sprite.h = 16 * 2;
                };
                auto drawPiece = [&](const ColorType block, autoTexture& minos) {
                    switch (block)
                    {
                    case empty:
                        minos.textureRegion.x = 16;
                        helper(minos);
                        break;
                    case Z:
                        minos.textureRegion.x = 32;
                        helper(minos);
                        break;
                    case L:
                        minos.textureRegion.x = 48;
                        helper(minos);
                        break;
                    case O:
                        minos.textureRegion.x = 64;
                        helper(minos);
                        break;
                    case S:
                        minos.textureRegion.x = 80;
                        helper(minos);
                        break;
                    case I:
                        minos.textureRegion.x = 96;
                        helper(minos);
                        break;
                    case J:
                        minos.textureRegion.x = 112;
                        helper(minos);
                        break;
                    case T:
                        minos.textureRegion.x = 128;
                        helper(minos);
                        break;
                    case line_clear:
                        minos.textureRegion.x = 144;
                        helper(minos);
                        break;
                    default:
                        break;
                    }
                };
                drawPiece(hold.piecedef[y][x], pieces);
                window.render(pieces);
            }
        }
    }

    SDL_Color color{};
    color.r = 0xff; color.g = 0xff; color.b = 0xff;
    if (placedPiece) {
        piecesPlaced++;
        placedPiece = false;
    }
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 timePassed = ((double)(now - timeWhenInit) / SDL_GetPerformanceFrequency()) * 1000;
    auto pps = std::to_string((static_cast<const double>(piecesPlaced) / timePassed) * 1000);
    std::string textbuf = "PPS: ";
    pps.erase(pps.length() - 4, 4);
    textbuf.append(pps);
    SDL_Surface* TextSurface = TTF_RenderText_Solid(font, textbuf.c_str(), color);
    SDL_Texture *text = window.CreateTextureFromSurface(TextSurface);
    SDL_Rect test = { 0, 610, 0, 0 };
    test.w = TextSurface->w;
    test.h = TextSurface->h;
    test.x = board_width_offset - test.w - 10;
    window.renderCopy(text, NULL, &test);

    textbuf = "APM: ";
    pps = std::to_string((static_cast<const double>(numDamageSent) / (timePassed / 60)) * 1000);
    pps.erase(pps.length() - 4, 4);
    textbuf.append(pps);
    SDL_FreeSurface(TextSurface);
    TextSurface = TTF_RenderText_Solid(font, textbuf.c_str(), color);
    SDL_DestroyTexture(text);
    text = window.CreateTextureFromSurface(TextSurface);
    test.y += test.h + 20;
    test.w = TextSurface->w;
    test.h = TextSurface->h;
    test.x = board_width_offset - test.w - 10;
    window.renderCopy(text, NULL, &test);

    textbuf = "damage sent: ";
    pps = std::to_string(numDamageSent);
    textbuf.append(pps);
    SDL_FreeSurface(TextSurface);
    TextSurface = TTF_RenderText_Solid(font, textbuf.c_str(), color);
    SDL_DestroyTexture(text);
    text = window.CreateTextureFromSurface(TextSurface);
    test.y += test.h + 20;
    test.w = TextSurface->w;
    test.h = TextSurface->h;
    test.x = board_width_offset - test.w - 10;
    window.renderCopy(text, NULL, &test);

    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(text);
}

Game::~Game()
{
    
}