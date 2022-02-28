#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Position
{
    int m_x;
    int m_y;

    Position (int x, int y): m_x(x), m_y(y){};
    friend std::ostream& operator<< (std::ostream& out, const Position& p);
};

enum class Color
{
    WHITE,
    BLACK
};

Position ReadInput(const std::string& enquiry);
