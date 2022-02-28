#include "gameengine.h"

Position ReadInput(const std::string& enquiry)
{
    while (true) // Loop until user enters a valid input
    {
        char x;
        int y;
        std::cout << enquiry << '\n';
        std::cin >> x >> y;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            x = toupper(x);
            if ((x >= 'A' && x <= 'H') && (y >= 1 && y <= 8))
            {
                return Position(-(y-8), x-'A');
            }
        }
    }
}

std::ostream& operator<< (std::ostream& out, const Position& p)
{
    return out << '(' << p.m_x << ',' << p.m_y << ')';
}
