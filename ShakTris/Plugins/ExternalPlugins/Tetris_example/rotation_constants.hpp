﻿#pragma once



//number of kicks srs has, including for initial
constexpr auto kicks = 5;

//number of kicks misamino 180 has not counting for initial
constexpr auto kicks180 = 12;

//left and right
//these are the only directions you can turn towards not including 180 due to it being a special case
constexpr auto turnDirections = 2;

//the number of kicks asc uses
constexpr auto ascKicks = 20;

constexpr int asc[ascKicks][2] = { 
                        {-1, 00}, {00, -1}, {-1, -1}, {00, -2}, {-1, -2},
                        {-2, 00}, {-2, -1}, {-2, -2}, {01, 00}, {01, -1},
                        {00, 01}, {-1, 01}, {-2, 01}, {01, -2}, {02, 00},
                        {00, 02}, {-1, 02}, {-2, 02}, {02, -1}, {02, -2} 
};

const std::array< std::array<Coord, kicks180>, number_of_RotationDirections>Iwallkick180data = { {
        {{{0,0},{0,-1},{0,-2},{0,1},{0,2},{1,0}}},
        {{{0,0},{1,0},{2,0},{-1,0},{-2,0},{0,-1}}},
        {{{0,0},{0,1},{0,2},{0,-1},{0,-2},{-1,0}}},
        {{{0,0},{1,0},{2,0},{-1,0},{-2,0},{0,1}}},

    } };
const std::array< Coord, number_of_RotationDirections>IPrecalculatedwallkick180offsets = { 
    {
        { 1,-1},
        {-1, 1},
        {-1, 1},
        { 1,-1},
    }
};
const std::array< std::array<Coord, kicks180>, number_of_RotationDirections> wallkick180data = { {
    {{// North -> South
        {0, 0},{ 1, 0},{ 2, 0},{ 1, 1},{ 2, 1},{-1, 0},{-2, 0},{-1, 1},{-2, 1},{ 0,-1},{ 3, 0},{-3, 0}
    }},
    {{// East -> West
        {0, 0},{ 0, 1},{ 0, 2},{-1, 1},{-1, 2},{ 0,-1},{ 0,-2},{-1,-1},{-1,-2},{ 1, 0},{ 0, 3},{ 0,-3}
    }},
    {{// South -> North
        {0, 0},{-1, 0},{-2, 0},{-1,-1},{-2,-1},{ 1, 0},{ 2, 0},{ 1,-1},{ 2,-1},{ 0, 1},{-3, 0},{ 3, 0}
    }},
    {{// West -> East
        {0, 0},{ 0, 1},{ 0, 2},{ 1, 1},{ 1, 2},{ 0,-1},{ 0,-2},{ 1,-1},{ 1,-2},{-1, 0},{ 0, 3},{ 0,-3}
    }}
} };


constexpr std::array<std::array<Coord, kicks>, number_of_RotationDirections> JLSTZPieceOffsetData = { {
    {{{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}}},
    {{{ 0, 0}, { 1, 0}, { 1,-1}, { 0, 2}, { 1, 2}}},
    {{{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}}},
    {{{ 0, 0}, {-1, 0}, {-1,-1}, { 0, 2}, {-1, 2}}},
} };

constexpr std::array<std::array<Coord, kicks>, number_of_RotationDirections> IPieceOffsetData = { {

    {{{ 0, 0}, {-1, 0}, { 2, 0}, {-1, 0}, { 2, 0}}},
    {{{-1, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0,-2}}},
    {{{-1, 1}, { 1, 1}, {-2, 1}, { 1, 0}, {-2, 0}}},
    {{{ 0, 1}, { 0, 1}, { 0, 1}, { 0,-1}, { 0, 2}}},


} };

constexpr std::array<std::array<Coord, kicks>, number_of_RotationDirections> OPieceOffsetData = { {
    {{{ 0, 0}}},
    {{{ 0,-1}}},
    {{{-1,-1}}},
    {{{-1, 0}}},
} };
constexpr std::array<Coord, number_of_RotationDirections> IPieceOffsetData180= { {
        { 0, 0},
        { 0,-1},
        {-1, 0},
        { 0, 0},
} };



