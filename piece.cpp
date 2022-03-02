#include "piece.h"

void Piece::setPiece(char t, Color c)
{
    m_type = t;
    m_color = c;
}

char Piece::getType() const
{
    return m_type;
}

Color Piece::getColor() const
{
    return m_color;
}

bool Piece::PawnMove   (int16_t start, int16_t target)
{

}
bool Piece::RookMove   (int16_t start, int16_t target, const Game& game)
{
    Position s{IndexToPosition(start)}, t{IndexToPosition(target)};
    if ((s.m_x == t.m_x) || (s.m_y == t.m_y))
    {
        if (game.checkLine(start, target))
        {
            m_hasMoved = true;
            return true;
        }
    }
    return false;
}
bool Piece::KnightMove (int16_t start, int16_t target)
{
    int16_t dx {abs(start - target)};
    std::vector <int16_t> correctValues {6, 10, 15, 17};
    for (int16_t entry : correctValues)
    {
        if (dx == entry)
        {
            m_hasMoved = true;
            return true;
        }
    }
    return false;
}
bool Piece::BishopMove (int16_t start, int16_t target, const Game& game)
{
    int16_t dx {abs(start - target)};
    if (dx % 7 == 0 || dx % 9 == 0)
    {
        m_hasMoved = true;
        return true;
    }
    return false;
}
bool Piece::QueenMove  (int16_t start, int16_t target, const Game& game)
{
    return RookMove(start, target, game) || BishopMove (start, target, game);
}
bool Piece::KingMove   (int16_t start, int16_t target)
{
    int16_t dx {abs(start - target)};
    std::vector <int16_t> correctValues {1, 7, 8, 9};
    for (int16_t entry : correctValues)
    {
        if (dx == entry)
        {
            m_hasMoved = true;
            return true;
        }
    }
    return false;
}
bool Piece::isMoveLegal(const Position& s, const Position& t, const Game& game)
{
    int16_t start {PositionToIndex(s)}, target{PositionToIndex(t)};
    if (start == target)
        return false;
    //Check if target square has piece of the same color
    if (game.getBoard().at(start).getColor() == game.getBoard().at(target).getColor())
        return false;

    char piece_type{toupper(m_type)};
    switch (piece_type)
    {
        case 'P': return PawnMove   (start, target);
        case 'N': return KnightMove (start, target);
        case 'K': return KingMove   (start, target);
        case 'R': return RookMove   (start, target, game);
        case 'B': return BishopMove (start, target, game);
        case 'Q': return QueenMove  (start, target, game);
        default : return false;
    }
}

