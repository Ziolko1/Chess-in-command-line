#pragma once
#include "includes.h"

class Piece
{
    char m_type;
    Color m_color;
public:
    Piece () : m_type(' '), m_color(Color::MAX_VALUE) {}
    Piece (char t, Color c) : m_type(t), m_color(c) {}
    void setPiece(char t, Color c);
    char getType();
};
