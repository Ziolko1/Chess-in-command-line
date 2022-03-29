#pragma once
#include <iostream> //IO
#include <string>   //IO buffer
#include <vector>   //container

struct Position
{
    char m_x;   //Column    -> A - H
    char m_y;   //Row       -> 1 - 8

    Position (char x, char y);
    Position (int16_t i);
    bool operator== (const Position& p) const;
};

struct SingleMove
{
    int16_t start, target;

    SingleMove(int16_t s, int16_t t);
};

enum class Color
{
    EMPTY,
    WHITE,
    BLACK
};

enum class MoveType
{
    NOT_VALID,
    MOVE,
    CHECK_COLLISION,
    PAWN_PUSH,
    PAWN_CAPTURE,
    PROMOTION,
    CASTLING
};

void tests();
Position ReadInput(const std::string& enquiry);
template <typename T>
T abs(T input);

Color getOppositeColor (Color input);
std::ostream& operator<< (std::ostream& out, const Position& p);
int16_t positionToIndex (const Position& p);

