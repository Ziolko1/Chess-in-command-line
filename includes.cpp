#include "includes.h"

void tests()
{
    //IndexToPosition and PositionToIndex transformations
    for (int i{0}; i<64; ++i)
    {
        Position x (IndexToPosition(i));
        std::cout << i << " translates to: " << x << '\t'
        << x << " translates back to: " << PositionToIndex(x) << '\n';
    }
    std::cout << '\n';
}

Position ReadInput(const std::string& enquiry)
{
    while (true) // Loop until user enters a valid input
    {
        char x;
        char y;
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
            if ((x >= 'A' && x <= 'H') && (y >= '1' && y <= '8'))
            {
                return Position(x,y);
            }
        }
    }
}

std::ostream& operator<< (std::ostream& out, const Position& p)
{
    return out << '(' << p.m_x << ',' << p.m_y << ')';
}

int16_t PositionToIndex (const Position& p)
{
    return p.m_x - 'A' + ('8' - p.m_y) * 8;
}

Position IndexToPosition (int16_t index)
{
    return {index%8 + 'A', '8' - index/8};
}
