
#pragma once


//number of kicks srs has not counting for initial
const int kicks = 4;

//number of kicks misamino 180 has not counting for initial
const int kicks180 = 5;

//left and right
//these are the only directions you can turn towards not including 180 due to it being a special case
const int turnDirections = 2;

//the number of kicks asc uses
const int ascKicks = 20;

const int asc[ascKicks][2] = { {-1, 00}, {00, -1}, {-1, -1}, {00, -2}, {-1, -2},
                        {-2, 00}, {-2, -1}, {-2, -2}, {01, 00}, {01, -1},
                        {00, 01}, {-1, 01}, {-2, 01}, {01, -2}, {02, 00},
                        {00, 02}, {-1, 02}, {-2, 02}, {02, -1}, {02, -2} };
const int Iwallkickdata[number_of_RotationDirections][turnDirections][kicks][2] = {
                {
        // North
        {
                        // West
                        {1, 0},
                        {-2, 0},
                        {1, 2},
                        {-2, -1},
                    },
                    {
                        // East
                        {2, 0},
                        {-1, 0},
                        {2, -1},
                        {-1, 2},
                    },
                },
                {
                    // East
                    {
                        // North
                        {-2, 0},
                        {1, 0},
                        {-2, 1},
                        {1, -2},
                    },
                    {
                        // South
                        {1, 0},
                        {-2, 0},
                        {1, 2},
                        {-2, -1},
                    },
                },
                {
                    // South
                    {
                        // East
                        {-1, 0},
                        {2, 0},
                        {-1, -2},
                        {2, 1},
                    },
                    {
                        // West
                        {-2, 0},
                        {1, 0},
                        {-2, 1},
                        {1, -2},
                    },
                },
                {
                    // West
                    {
                        // South
                        {2, 0},
                        {-1, 0},
                        {2, -1},
                        {-1, 2},
                    },
                    {
                        // North
                        {-1, 0},
                        {2, 0},
                        {-1, -2},
                        {2, 1},
                    },
                },
};
const int srsplusIwallkickdata[number_of_RotationDirections][turnDirections][kicks][2] = {
    {
        // O
        {
            // L 3
            {1, 0},
            {-2, 0},
            {1, 2},
            {-2, -1},
        },
        {
            // R 1
            {-1, 0},
            {2, 0},
            {-1, 2},
            {2, -1},
        },
    },
    {
        // R 1
        {
            // O
            {-2, 0},
            {1, 0},
            {-2, 1},
            {1, -2},
        },
        {
            // 2
            {1, 0},
            {-2, 0},
            {1, 2},
            {-2, -1},
        },
    },
    {
        // 2
        {
            // R 1
            {2, 0},
            {-1, 0},
            {2, 1},
            {-1, -2},
        },
        {
            // L 3
            {-2, 0},
            {1, 0},
            {-2, 1},
            {1, -2},
        },
    },
    {
        // L 3
        {
            // 2
            {-1, 0},
            {2, 0},
            {-1, 2},
            {2, -1},
        },
        {
            // O
            {-1, 0},
            {2, 0},
            {-1, -2},
            {2, 1},
        },
    },
};
const int wallkickdata[number_of_RotationDirections][turnDirections][kicks][2] = {
    // 0 = spawn state
    // R = state resulting from a clockwise rotation("right") from spawn
    // L = state resulting from a counter - clockwise("left") rotation from
    // spawn
    // 2 = state resulting from 2 successive rotations in either direction
    // from spawn.
    //{x. y}

    {
        // O
        {
            // L
            {-1, 0},
            {-1, 1},
            {0, -2},
            {-1, -2},
        },
        {
            // R
            {1, 0},
            {1, 1},
            {0, -2},
            {1, -2},
        },
    },
    {
        // R
        {
            // O
            {-1, 0},
            {-1, -1},
            {0, 2},
            {-1, 2},
        },
        {
            // 2
            {-1, 0},
            {-1, -1},
            {0, 2},
            {-1, 2},
        },
    },
    {
        // 2
        {
            // R
            {1, 0},
            {1, 1},
            {0, -2},
            {1, -2},
        },
        {
            // L
            {-1, 0},
            {-1, 1},
            {0, -2},
            {-1, -2},
        },
    },
    {
        // L
        {
            // 2
            {1, 0},
            {1, -1},
            {0, 2},
            {1, 2},
        },
        {
            // O
            {1, 0},
            {1, -1},
            {0, 2},
            {1, 2},
        },
    },
};
const int Iwallkick180data[number_of_RotationDirections][kicks180][2] = { {// North -> South
                                        {0, 1},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0}},
                                       {// East -> West
                                        {-1, 0},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0}},
                                       {// South -> North
                                        {0, -1},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0}},
                                       {// West -> East
                                        {1, 0},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0},
                                        {0, 0}} };
const int wallkick180data[number_of_RotationDirections][kicks180][2] = {
                                      {// North -> South
                                       {0, 1},
                                       {-1, 1},
                                       {1, 1},
                                       {-1, 0},
                                       {1, 0}},
                                      {// East -> West
                                       {-1, 0},
                                       {-1, 2},
                                       {-1, 1},
                                       {0, 2},
                                       {0, 1}},
                                      {// South -> North
                                       {0, -1},
                                       {1, -1},
                                       {-1, 1},
                                       {1, 0},
                                       {-1, 0}},
                                      {// West -> East
                                       {1, 0},
                                       {1, 2},
                                       {1, 1},
                                       {0, 2},
                                       {0, 1}} };