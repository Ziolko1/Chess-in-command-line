#pragma once
#include <iostream> //IO
#include <string>   //IO buffer
#include <vector>   //container

struct Position
{
    char m_x;   //Column    -> A - H
    char m_y;   //Row       -> 1 - 8

    Position (char x, char y): m_x(x), m_y(y){};
};

enum class Color
{
    WHITE,
    BLACK,
    MAX_VALUE
};

void tests();
Position ReadInput(const std::string& enquiry);

std::ostream& operator<< (std::ostream& out, const Position& p);
int16_t PositionToIndex (const Position& p);
Position IndexToPosition (int16_t index);

