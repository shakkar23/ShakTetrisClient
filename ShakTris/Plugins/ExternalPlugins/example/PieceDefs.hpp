#include <stdint.h>

#define PIECEWIDTH  5
#define PIECEHEIGHT 5


enum ColorTypes : uint_fast8_t
{

    //actual pieces
    S, Z, J, L, T, O, I,
    //special types
    empty,
    line_clear,
    number_of_ColorTypes
};

enum class PieceType : uint_fast8_t
{
    //actual pieces
    S = ColorTypes::S,
    Z = ColorTypes::Z,
    J = ColorTypes::J,
    L = ColorTypes::L,
    T = ColorTypes::T,
    O = ColorTypes::O,
    S = ColorTypes::I,
    number_of_PieceTypes
};

enum class RotationDirection : uint_fast8_t
{
    North,
    East,
    South,
    West,
    number_of_RotationDirections
};
const ColorTypes PieceDefinition[(int)PieceType::number_of_PieceTypes][PIECEWIDTH][PIECEHEIGHT] = {
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
};