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

enum Color
{
    EMPTY,
    WHITE,
    BLACK
};

enum class MoveType
{
    NOT_VALID,
    MOVE,
    PAWN_PUSH,
    PAWN_CAPTURE,
    EN_PASSANT,
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

