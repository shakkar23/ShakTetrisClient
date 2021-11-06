#pragma once
#include <stdint.h>

// the definition needs to be a square, otherwise change how you rotate pieces pls
#define PIECEWIDTHANDHEIGHT 5
#define PIECEWIDTH  PIECEWIDTHANDHEIGHT
#define PIECEHEIGHT PIECEWIDTHANDHEIGHT


enum ColorType : uint_fast8_t {

    //actual pieces
    S, Z, J, L, T, O, I,
    //special types
    empty,
    line_clear,
    number_of_ColorTypes
};

enum class PieceType : uint_fast8_t {
    //actual pieces
    S = ColorType::S,
    Z = ColorType::Z,
    J = ColorType::J,
    L = ColorType::L,
    T = ColorType::T,
    O = ColorType::O,
    I = ColorType::I,
    empty = ColorType::empty,
    number_of_PieceTypes
};
constexpr ColorType PieceTypeToColorType(PieceType color) {
    switch (color)
    {
    case PieceType::S:
        return S;
    case PieceType::Z:
        return Z;
    case PieceType::J:
        return J;
    case PieceType::L:
        return L;
    case PieceType::T:
        return T;
    case PieceType::O:
        return O;
    case PieceType::I:
        return I;
    case PieceType::empty:
    case PieceType::number_of_PieceTypes:
    default:
        return empty;
    }
    return empty;
}
enum RotationDirection : uint_fast8_t {
    North,
    East,
    South,
    West,
    number_of_RotationDirections
};
enum TurnDirection : uint_fast8_t {
    Left,
    Right,
    number_of_TurnDirections,
    oneEighty,
};

const ColorType PieceDefinition[(int)PieceType::number_of_PieceTypes][PIECEWIDTH][PIECEHEIGHT] = {
    // the /**/ is to indicate the center of the definition, I thought it was clever 

    {//S
        {empty,empty,empty,empty,empty,},
        {empty,empty,S    ,S    ,empty,},
        {empty,S    ,S/**/,empty,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//Z
        {empty,empty,empty,empty,empty,},
        {empty,Z    ,Z    ,empty,empty,},
        {empty,empty,Z/**/,Z    ,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//J
        {empty,empty,empty,empty,empty,},
        {empty,J    ,empty,empty,empty,},
        {empty,J    ,J/**/,J    ,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//L
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,L    ,empty,},
        {empty,L    ,L/**/,L    ,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//T
        {empty,empty,empty,empty,empty,},
        {empty,empty,T    ,empty,empty,},
        {empty,T    ,T/**/,T    ,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//O
        {empty,empty,empty,empty,empty,},
        {empty,empty,O    ,O    ,empty,},
        {empty,empty,O/**/,O    ,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//I
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,I    ,I/**/,I    ,I    ,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,}

    },
    {//NULL
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,},
        {empty,empty,empty,empty,empty,},

    },
};
