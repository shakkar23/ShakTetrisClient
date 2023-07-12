#pragma once

#include "PieceDefs.hpp"
#include "../../../../Platform/SDL2/headers/RenderWindow.hpp"
#include "../../../../Platform/SDL2/headers/Game.hpp"
#include "../../../../Platform/SDL2/headers/entity.hpp"
#include "../../../../Platform/SDL2/Audio/Audio.hpp"
#include "combo_table.hpp"
#include "damageTable.hpp"
#include "ppt.h"
#include <vector>
#include <span>
#include <cassert>
#include <algorithm>
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

constexpr inline auto BOARDWIDTH = 10;
constexpr inline auto VISUALBOARDHEIGHT = 20;
constexpr inline auto LOGICALBOARDHEIGHT = 40;

class Board;
class Piece {
public:
    Piece(PieceType kind, int_fast8_t x = 4, int_fast8_t y = VISUALBOARDHEIGHT - 2, RotationDirection spin = RotationDirection::North) {
        //force the RNG to throw away its previous bag, and make a new one

        this->kind = kind;
        setX(x); setY(y);
        this->spin = spin;

        //populate local piece definition
        for (size_t i = 0; i < MINOSINAPIECE; i++)
        {
            piecedef[i] = PieceDefintions[PieceTypeToColorType(kind)][i];
        }
        //match up the spin direction of the local piece definition with what is given by the params
        switch (spin)
        {
        case North:
            break;
        case East:
            rotateCCW(); rotateCCW(); rotateCCW();
            break;
        case South:
            rotateCCW(); rotateCCW();
            break;
        case West:
            rotateCCW();
            break;
        default:
            break;
        }
    }
    Piece() = delete;

    friend Board;

    // rotates the piece 90 degrees counter clock wise
    // Thanks MinusKelvin for the idea of using coordinates and not a definition
    void rotateCW()
    {
        for (auto& coords : piecedef)
        {
            std::swap(coords.y, coords.x);
            coords.y = -coords.y;
        }
    }

    void rotateCCW()
    {
        for (auto& coords : piecedef)
        {
            std::swap(coords.y, coords.x);
            coords.x = -coords.x;
        }
    }
    void setX(int_fast8_t setter) {
        x = setter;
    }
    void setY(int_fast8_t setter) {
        y = setter;
    }
    std::array<Coord, MINOSINAPIECE> piecedef{};
    PieceType kind{};
    RotationDirection spin{};
    int_fast8_t x{};
    int_fast8_t y{};

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
            {
                if (mino != ColorType::empty)
                    mino = ColorType::line_clear;
            }
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
        // clear the line in question
        for (size_t i = 0; i < BOARDWIDTH; i++)
        {
            board.at(i).at(whichLine) = empty;
        }

        //pull down the rest of the lines above the cleared line down
        for (size_t w = 0; w < BOARDWIDTH; w++)
        {
            for (size_t h = whichLine; h < LOGICALBOARDHEIGHT; h++)
            {
                if (h == (LOGICALBOARDHEIGHT - 1))
                {

                    board.at(w).at(h) = empty;
                    break;
                }
                else {
                    board.at(w).at(h) = board.at(w).at((h + 1));
                }
            }

        }
    }
    void sonicDrop(Piece& piece) {
        while (trySoftDrop(piece));
    }

    bool trySoftDrop(Piece& piece) {
        piece.setY(piece.y - 1);
        if (isCollide(piece)) {
            piece.setY(piece.y + 1); // if it collided, go back up where it should be safe
            return false;
        }
        return true;
    }

    void setPiece(const Piece& piece) {
        new Shakkar::autoAudio("Asset/Sounds/Sound.wav", (128 / 5));

        for (auto& coord : piece.piecedef)
        {
            if ((((0 <= (coord.y + piece.y)) && ((coord.y + piece.y) < LOGICALBOARDHEIGHT))) && (((0 <= (coord.x + piece.x)) && ((coord.x + piece.x) < BOARDWIDTH)))) //if inbounds of board
            {
                board.at(coord.x + piece.x).at((coord.y + piece.y)) = PieceTypeToColorType(piece.kind);
            }
        }
    }
    bool isCollide(const Piece& piece) {

        for (auto& coord : piece.piecedef)
        {

            if ((((0 <= (coord.y + piece.y)) && ((coord.y + piece.y) < LOGICALBOARDHEIGHT))) && (((0 <= (coord.x + piece.x)) && ((coord.x + piece.x) < BOARDWIDTH)))) //if inbounds of board
            {
                if (board.at((coord.x + piece.x)).at((coord.y + piece.y)) != empty) // is the cell in the board matrix empty
                    return true;
            }

            if (((coord.x + piece.x) < 0) || ((coord.x + piece.x) >= BOARDWIDTH)) // cant be out of bounds on either direction
            {
                return true;
            }

            if ((coord.y + piece.y) < 0) // can be above, but not below the board
            {
                return true;
            }

        }
        return false;
    }

    constexpr const char colorTypeToString(const ColorType color) {
        switch (color)
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

    std::array< std::array<ColorType, (LOGICALBOARDHEIGHT)>, BOARDWIDTH> board{};
};

constexpr int_fast16_t matrixXPos = (((DEFAULT_SCREEN_WIDTH - (224 * 3)) / 3) - 50);
constexpr int_fast16_t matrixYPos = (((DEFAULT_SCREEN_HEIGHT - (299 * 3)) / 3) - 100);
constexpr int softdropCountdownMAX = (UPDATES_A_SECOND);
constexpr uint_fast8_t pieceSpawnDelayMAX = 0;
constexpr uint_fast16_t lockDelayMAX = (UPDATES_A_SECOND);
constexpr auto perfectClearDamage = 10;
constexpr auto backToBackBonus = 2;
class Game
{
public:
// these are in miliseconds
    uint_fast16_t dasSetting = 80; 
    uint_fast16_t arrSetting = 0;

    Game();
    ~Game();

    void gameLogic(const Shakkar::inputBitmap& input, const Shakkar::inputBitmap& prevInput);
    void render(RenderWindow& window);

    void Init(RenderWindow& window) {
        hold = Piece(PieceType::empty);
        queue.clear();
        queue.reserve(7);
        forceReRollBag();

        currentPiece = Piece(getRandPiece());

        for (size_t i = 0; i < 7; i++)
        {       
            queue.emplace_back(Piece(getRandPiece()));
        }
		
            this->ghostPieces       .load(window,"Asset/Sprites/exampleAssets/ghostPieces.png",0, 0, 16);
            this->pieces            .load(window,"Asset/Sprites/exampleAssets/TetrisPieces.png",0, 0, 16);
            this->matrix            .load(window,"Asset/Sprites/Tetris_images/Matrix.png"); // original size is 224 by 299
            this->background        .load(window, "Asset/Sprites/exampleAssets/TetrisBackground.png"); //1080p background
		
        if (!font)
            this->font = TTF_OpenFont("Asset/Sprites/exampleAssets/font.ttf", 36);
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


        this->matrix.destRect = { matrixX,matrixY,
                                (224 * 4),(299 * 4) };

        /*
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
        ghostPieces.sprite = { 0,0,24,24 };*/
        pieces.updateSection(0, 0);
        ghostPieces.updateSection(0, 0);
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

    bool tryRotate(Piece& piece, TurnDirection direction) {
        auto incrRotClockWise = [&](RotationDirection& spin) {
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
                bool topright(isEmpty(piece.x + 1, piece.y + 1, board));
                bool topleft(isEmpty(piece.x - 1, piece.y + 1, board));
                bool bottomright(isEmpty(piece.x + 1, piece.y - 1, board));
                bool bottomleft(isEmpty(piece.x - 1, piece.y - 1, board));
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
            piece.rotateCW();
        }
        else if (direction == Left)
        {
            piece.rotateCCW();
        }
        else if (direction == oneEighty)
        {
            piece.rotateCCW();
            piece.rotateCCW();
        }

        // spinclockwise should be a bool, but it can also be 2 as in rotating twice
        // in one frame aka 180 spin
        if (direction != TurnDirection::oneEighty) {
            RotationDirection nextDir = piece.spin;
            if (direction == Right)
                incrRotClockWise(nextDir);
            else if (direction == Left)
            {
                incrRotClockWise(nextDir); incrRotClockWise(nextDir); incrRotClockWise(nextDir);
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

                piece.setX(x + (*offsetData)[i].x - (*nextOffset)[i].x);
                piece.setY(y + (*offsetData)[i].y - (*nextOffset)[i].y);

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
            incrRotClockWise(nextDir); incrRotClockWise(nextDir);

            auto* kickdata = &wallkick180data[piece.spin];
            bool isI = false;
            if (piece.kind == PieceType::I)
            {
                isI = true;
                kickdata = &Iwallkick180data[piece.spin];
            }

            for (int i = 0; i < 12; ++i) {

                piece.setX(x + ((*kickdata)[i].x + (isI * IPrecalculatedwallkick180offsets[piece.spin].x)));
                piece.setY(y - ((*kickdata)[i].y + (isI * IPrecalculatedwallkick180offsets[piece.spin].y)));

                if (!board.isCollide(piece)) {
                    piece.spin = nextDir;
                    TspinDetection(piece, board, Tspinned);
                    return true;
                }
            }
            piece.setX(x); piece.setY(y);
        }

        //rotate the matrix back if nothing worked
        if (direction == Right) {
            piece.rotateCCW();
        }
        else if (direction == Left)
        {
            piece.rotateCW();
        }
        else if (direction == oneEighty)
        {
            piece.rotateCCW();
            piece.rotateCCW();
        }
        return false;
    }

    Board board;
    Sprite background;
    Sprite matrix;
    SpriteSheet pieces;
    SpriteSheet ghostPieces;
    Texture matrixBackground;
    std::vector<Piece> queue{};
    Piece hold{ PieceType::empty };
    Piece currentPiece{ PieceType::empty };
    TTF_Font* font{};
    Uint64 timeWhenInit{};
    int32_t piecesPlaced{};
    int32_t softdropCountdown = softdropCountdownMAX;
    int32_t pieceSpawnDelay = pieceSpawnDelayMAX;
    int16_t matrixX = matrixXPos;
    int16_t matrixY = matrixYPos;

    uint16_t dasIterator = 0;
    uint16_t arrIterator = 0;
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
    else if (justPressed(prevInput.right, input.right)) {
        rightPressedMostRecent = true;
        leftPressedMostRecent = false;
    }

    bool leftState{};
    bool rightState{};

    leftState = (rightPressedMostRecent && input.right) ? false : input.left;
    rightState = (leftPressedMostRecent && input.left) ? false : input.right;

    if (checkForLineClear) {
        int linesCleared = board.clearLines();
        bool perfectCleared = true;
        for (auto& row : board.board) {
            for (auto& mino : row)
            {
                if (mino == empty)
                    continue;
                else {
                    perfectCleared = false;
                    break;
                }
            }
        }
        if (linesCleared == 0)
            currentCombo = 0;
        auto tmp1 = std::clamp(int(linesCleared), 0, DAMAGETABLESIZE - 1);
        auto tmp2 = std::clamp(int(currentCombo), 0, COMBOTABLESIZE  - 1);
        if (perfectCleared) {
            numDamageSent += perfectClearDamage + comboTable[tmp2];
        }
        else if (Tspinned) {
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
                numDamageSent += backToBackBonus;
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

                }
                else
                    softdropCountdown = softdropCountdownMAX;
            }
            else {

                if (input.softDrop)
                    softdropCountdown -= 40;
                else
                    softdropCountdown -= 1;
            }
            // rotate right logic
            if (justPressed(prevInput.rotLeft, input.rotLeft))
                tryRotate(currentPiece, TurnDirection::Left);

            //rotate left logic
            else if (justPressed(prevInput.rotRight, input.rotRight))
                tryRotate(currentPiece, TurnDirection::Right);

            // 180 logic
            else if (justPressed(prevInput.rot180, input.rot180))
                tryRotate(currentPiece, TurnDirection::oneEighty);

            //sonic drop logic
            if (prevInput.sonicDrop)
                board.sonicDrop(currentPiece);

            // hold logic
            if (justPressed(prevInput.hold, input.hold))
            {
                if (!alreadyHeld) {
                    std::swap(currentPiece, hold);
                    currentPiece.setX(4);
                    currentPiece.setY(VISUALBOARDHEIGHT - 1);

                    switch (currentPiece.spin)
                    {
                    case North:
                        break;
                    case East:
                        currentPiece.rotateCCW();
                        break;
                    case South:
                        currentPiece.rotateCCW(); currentPiece.rotateCCW();
                        break;
                    case West:
                        currentPiece.rotateCW();
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
                        hold.rotateCCW();
                        break;
                    case South:
                        hold.rotateCCW(); hold.rotateCCW();
                        break;
                    case West:
                        hold.rotateCW();
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

                    this->gameLogic(input, input);
                }
            }

            //harddrop logic
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

    }
    else
        pieceSpawnDelay--;
}


void Game::render(RenderWindow& window) {
    window.clear();
    background.render(window);


    matrix.render(window);
    auto doesPieceHaveMinoHere = [](Piece& piece, int x, int y) {
        for (auto& coord : piece.piecedef)
            if (((coord.x + piece.x) == x) && ((coord.y + piece.y) == y)) {
                return true;
            }
        return false;
    };
    auto doesVisualHaveMinoHere = [](Piece& piece, int x, int y) {
        for (auto& coord : piece.piecedef)
            if (((coord.x + 2) == x) && ((coord.y + 2) == y)) {
                return true;
            }
        return false;
    };
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
            auto helper = [&](SpriteSheet& minos) {
                minos.destRect.x = board_width_offset + (width * (24 * 2));
                minos.destRect.w = 16 * 3;
                minos.destRect.y = board_height_offset + ((VISUALBOARDHEIGHT - height - 1) * (24 * 2));
                minos.destRect.h = 16 * 3;
            };
            auto drawPiece = [&](ColorType block, SpriteSheet& minos) {
                switch (block)
                {
                case empty:
                    minos.srcRect.x = 16;
                    helper(minos);
                    break;
                case Z:
                    minos.srcRect.x = 32;
                    helper(minos);
                    break;
                case L:
                    minos.srcRect.x = 48;
                    helper(minos);
                    break;
                case O:
                    minos.srcRect.x = 64;
                    helper(minos);
                    break;
                case S:
                    minos.srcRect.x = 80;
                    helper(minos);
                    break;
                case I:
                    minos.srcRect.x = 96;
                    helper(minos);
                    break;
                case J:
                    minos.srcRect.x = 112;
                    helper(minos);
                    break;
                case T:
                    minos.srcRect.x = 128;
                    helper(minos);
                    break;
                case line_clear:
                    minos.srcRect.x = 144;
                    helper(minos);
                    break;
                default:
                    break;
                }
            };
            if (doesPieceHaveMinoHere(currentPiece, width, height))
            {
                drawPiece(PieceTypeToColorType(currentPiece.kind), pieces);
                pieces.render(window);

            }
            else if (doesPieceHaveMinoHere(ghost, width, height))
            {
                drawPiece(PieceTypeToColorType(ghost.kind), ghostPieces);
                ghostPieces.render(window);
            }
            else {
                drawPiece(board.board[width][height], pieces);
                pieces.render(window);

            }
        }
    }

    int16_t queue_width_offset = board_width_offset + (122 * 4) - 1 - 1;
    int16_t queue_height_offset = board_height_offset;

    //render queue 5 pieces to be seen, each with its own matrix of a 5x5 view
    for (size_t q = 0; q < 5; q++)
    {
        for (int y = 0, realy = 4; y < 5; y++, realy--)
            //for (int y = 0; y < PIECEHEIGHT; y++)
        {
            for (int x = 0; x < 5; x++)
                //for (int x = PIECEWIDTH -1; x >= 0; x--)
            {
                auto helper = [&](SpriteSheet& minos) {
                    minos.destRect.x = queue_width_offset + (x * (16 * 2));
                    minos.destRect.w = 16 * 2;
                    minos.destRect.y = queue_height_offset + ((y) * (16 * 2));
                    minos.destRect.h = 16 * 2;
                };
                auto drawPiece = [&](ColorType block, SpriteSheet& minos) {
                    switch (block)
                    {
                    case empty:
                        minos.srcRect.x = 16;
                        helper(minos);
                        break;
                    case Z:
                        minos.srcRect.x = 32;
                        helper(minos);
                        break;
                    case L:
                        minos.srcRect.x = 48;
                        helper(minos);
                        break;
                    case O:
                        minos.srcRect.x = 64;
                        helper(minos);
                        break;
                    case S:
                        minos.srcRect.x = 80;
                        helper(minos);
                        break;
                    case I:
                        minos.srcRect.x = 96;
                        helper(minos);
                        break;
                    case J:
                        minos.srcRect.x = 112;
                        helper(minos);
                        break;
                    case T:
                        minos.srcRect.x = 128;
                        helper(minos);
                        break;
                    case line_clear:
                        minos.srcRect.x = 144;
                        helper(minos);
                        break;
                    default:
                        break;
                    }
                };
                if (doesVisualHaveMinoHere(queue[q], x, realy))
                {
                    drawPiece(PieceTypeToColorType(queue[q].kind), pieces);
                }
                else
                    drawPiece(empty, pieces);
                pieces.render(window);
            }
        }
        queue_height_offset += (2 * 4);
        queue_height_offset += (5 * 16 * 2);
    }


    const int16_t hold_width_offset = board_width_offset - (42 * 4);
    const int16_t hold_height_offset = board_height_offset;

    //render the holds
    for (int h = 0; h < 1; h++)
    {
        for (int y = 0, realY = 4; y < 5; y++, realY--)
            //for (int y = 0; y < PIECEHEIGHT; y++)
        {
            for (int x = 0; x < 5; x++)
                //for (int x = PIECEWIDTH -1; x >= 0; x--)
            {
                auto helper = [&](SpriteSheet& minos) {
                    minos.destRect.x = hold_width_offset + (x * (16 * 2));
                    minos.destRect.w = 16 * 2;
                    minos.destRect.y = hold_height_offset + ((y) * (16 * 2));
                    minos.destRect.h = 16 * 2;
                };
                auto drawPiece = [&](const ColorType block, SpriteSheet& minos) {
                    switch (block)
                    {
                    case empty:
                        minos.srcRect.x = 16;
                        helper(minos);
                        break;
                    case Z:
                        minos.srcRect.x = 32;
                        helper(minos);
                        break;
                    case L:
                        minos.srcRect.x = 48;
                        helper(minos);
                        break;
                    case O:
                        minos.srcRect.x = 64;
                        helper(minos);
                        break;
                    case S:
                        minos.srcRect.x = 80;
                        helper(minos);
                        break;
                    case I:
                        minos.srcRect.x = 96;
                        helper(minos);
                        break;
                    case J:
                        minos.srcRect.x = 112;
                        helper(minos);
                        break;
                    case T:
                        minos.srcRect.x = 128;
                        helper(minos);
                        break;
                    case line_clear:
                        minos.srcRect.x = 144;
                        helper(minos);
                        break;
                    default:
                        break;
                    }
                };
                if (doesVisualHaveMinoHere(hold, x, realY))
                {
                    drawPiece(PieceTypeToColorType(hold.kind), pieces);
                }
                else
                    drawPiece(empty, pieces);
                pieces.render(window);
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
    SDL_Texture* text = window.CreateTextureFromSurface(TextSurface);
    SDL_Rect test = { 0, 610, 0, 0 };
    test.w = TextSurface->w;
    test.h = TextSurface->h;
    test.x = board_width_offset - test.w - 10;
    SDL_SetTextureColorMod(text, 255, 0, 0);
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
    SDL_SetTextureColorMod(text, 255, 0, 0);
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
    SDL_SetTextureColorMod(text, 255, 0, 0);
    window.renderCopy(text, NULL, &test);

    textbuf = "normalized Cords";
    SDL_FreeSurface(TextSurface);
    TextSurface = TTF_RenderText_Solid(font, textbuf.c_str(), color);
    SDL_DestroyTexture(text);
    text = window.CreateTextureFromSurface(TextSurface);
    test.y += test.h + 20;
    test.w = TextSurface->w;
    test.h = TextSurface->h;
    test.x = board_width_offset - test.w - 10;
    SDL_SetTextureColorMod(text, 255, 0, 0);
    window.renderCopy(text, NULL, &test);

    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(text);
}

Game::~Game()
{

}