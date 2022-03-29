#include "includes.h"

Position::Position (char x, char y): m_x(x), m_y(y) {}
Position::Position (int16_t i) : m_x (i%8 + 'A'), m_y ('8' - i/8) {}
SingleMove::SingleMove(int16_t s, int16_t t) : start(s), target(t) {}

void tests()
{
    //Int16_t constructor and PositionToIndex transformations test
    for (int i{0}; i<64; ++i)
    {
        Position x (i);
        std::cout << i << " translates to: " << x
        << ", translates back to: " << positionToIndex(x) << '\n';
    }
    std::cout << '\n';
}

Position ReadInput(const std::string& enquiry)
{
    while (true) // Loop until user enters a valid input
    {
        char x,y;
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

template <typename T>
T abs(T input)
{
    return input > 0 ? input : -input;
}
bool Position::operator== (const Position& p) const
{
    return ((m_x == p.m_x) && (m_y == p.m_y));
}
std::ostream& operator<< (std::ostream& out, const Position& p)
{
    return out << '(' << p.m_x << ',' << p.m_y << ')';
}

int16_t positionToIndex (const Position& p)
{
    return p.m_x - 'A' + ('8' - p.m_y) * 8;
}

Color getOppositeColor (Color input)
{
    if (input == Color::WHITE)
        return Color::BLACK;
    if (input == Color::BLACK)
        return Color::WHITE;
    return Color::EMPTY;
}
