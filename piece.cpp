#include "piece.h"

Piece::Piece () : m_type(' '), m_color(Color::EMPTY) {}
Piece::Piece (char t, Color c) : m_type(t), m_color(c) {}
void Piece::setPiece(char t, Color c)
{
    m_type = t;
    m_color = c;
}
void Piece::setMoved()
{
    m_hasMoved = true;
}
bool Piece::getMoved() const
{
    return m_hasMoved;
}

char Piece::getType() const
{
    return m_type;
}

Color Piece::getColor() const
{
    return m_color;
}
bool Piece::operator== (const Piece& p)
{
    if (toupper(m_type) == toupper(p.m_type) && m_color == p.m_color)
        return true;
    return false;
}

//   X-27  X-26  X-25  X-24  X-23  X-22  X-21  X-20
//   X-19  X-18  X-17  X-16  X-15  X-14  X-13  X-12
//   X-11  X-10  X-9   X-8   X-7   X-6   X-5   X-4
//   X-3   X-2   X-1    X    X+1   X+2   X+3   X+4
//   X+5   X+6   X+7   X+8   X+9   X+10  X+11  X+12
//   X+13  X+14  X+15  X+16  X+17  X+18  X+19  X+20
//   X+21  X+22  X+23  X+24  X+25  X+26  X+27  X+28
//   X+29  X+30  X+31  X+32  X+33  X+34  X+35  X+36

MoveType Piece::PawnMove   (int16_t start, int16_t target) const
{
    int16_t dir {m_color == Color::WHITE ? -1 : 1}, dx{target - start};
    if (dx == dir * 8)                          //Standard move
        return MoveType::MOVE;

    if (dx == dir * 16 && m_hasMoved == false)  //Double move
        return MoveType::PAWN_PUSH;

    if (dx == dir * 7 || dx == dir * 9)         //Capture diagonally)
        return MoveType::PAWN_CAPTURE;

    return MoveType::NOT_VALID;
}
MoveType Piece::RookMove   (int16_t start, int16_t target) const
{
    Position s(start), t(target);
    if ((s.m_x == t.m_x) || (s.m_y == t.m_y))   //One of the coordinates is the same
        return MoveType::MOVE;

    return MoveType::NOT_VALID;
}
MoveType Piece::KnightMove (int16_t start, int16_t target) const
{
    int16_t dx {abs(start - target)};
    std::vector <int16_t> correctValues {6, 10, 15, 17};
    for (int16_t entry : correctValues)
        if (dx == entry)
            return MoveType::MOVE;

    return MoveType::NOT_VALID;
}
MoveType Piece::BishopMove (int16_t start, int16_t target) const
{
    int16_t dx {abs((start%8) - (target%8))}, dy{abs((start/8) - (target/8))};
    if (dx == dy)
            return MoveType::MOVE;

    return MoveType::NOT_VALID;
}
MoveType Piece::QueenMove  (int16_t start, int16_t target) const
{
    if (RookMove(start, target) == MoveType::MOVE
        || BishopMove (start, target) == MoveType::MOVE)
        return MoveType::MOVE;
    else
        return MoveType::NOT_VALID;
}
MoveType Piece::KingMove   (int16_t start, int16_t target) const
{
    int16_t dx {abs(start - target)};
    std::vector <int16_t> correctValues {1, 7, 8, 9};
    for (int16_t entry : correctValues)
    {
        if (dx == entry)
        {
            return MoveType::MOVE;
        }
    }
    if (dx == 2 && !m_hasMoved)     //Player is trying to move king 2 cells -> castiling
    {
        return MoveType::CASTLING;
    }
    return MoveType::NOT_VALID;
}
//Check if piece is changing its board position properly
MoveType Piece::isMoveLegal(const Position& s, const Position& t) const
{
    //Check if piece is actually moving and not skipping turn
    if (s == t)
        return MoveType::NOT_VALID;
    int16_t start {positionToIndex(s)}, target{positionToIndex(t)};

    char piece_type{toupper(m_type)};
    switch (piece_type)
    {
        case 'P': return PawnMove   (start, target);
        case 'N': return KnightMove (start, target);
        case 'K': return KingMove   (start, target);
        case 'R': return RookMove   (start, target);
        case 'B': return BishopMove (start, target);
        case 'Q': return QueenMove  (start, target);
        default : return MoveType::NOT_VALID;
    }
}
MoveType Piece::isMoveLegal(int16_t start, int16_t target) const
{
    return Piece::isMoveLegal(Position{start}, Position{target});
}
