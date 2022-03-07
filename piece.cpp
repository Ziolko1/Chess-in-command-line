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

//   X-27  X-26  X-25  X-24  X-23  X-22  X-21  X-20
//   X-19  X-18  X-17  X-16  X-15  X-14  X-13  X-12
//   X-11  X-10  X-9   X-8   X-7   X-6   X-5   X-4
//   X-3   X-2   X-1    X    X+1   X+2   X+3   X+4
//   X+5   X+6   X+7   X+8   X+9   X+10  X+11  X+12
//   X+13  X+14  X+15  X+16  X+17  X+18  X+19  X+20
//   X+21  X+22  X+23  X+24  X+25  X+26  X+27  X+28
//   X+29  X+30  X+31  X+32  X+33  X+34  X+35  X+36

bool Piece::checkLine(int16_t start, int16_t target, const Game& game)
{
    //I am not sure if this function should live in this class
    //Check if a straight, horizontal, vertical or diagonal line can be made from provided points
    //If it is horizontal or vertical only one coordinate will change     (queen, rook)
    //If is is diagonal both coordinates have to change equal amount      (queen, bishop)
    //We do not have to check current piece position and target - these will be checked by caller
    int changeX {(target - start) %8};
    int changeY {(target - start) /8};

    if ((!changeX && changeY) || (changeX && !changeY) || abs(changeX)==abs(changeY))
    {
        std::vector<int16_t> vPos;
        while (changeX || changeY)
        {
            //(in/de)crease change before adding position to skip starting position
            if (changeX)
                (changeX>0 ? --changeX : ++changeX);
            if (changeY)
                (changeY>0 ? --changeY : ++changeY);
            //Check to avoid adding target position
            if (changeX || changeY)
                vPos.push_back(target + changeX + changeY*8);
        }
        for (auto const &element : vPos)
        {
            if (game.isPossitionOccupied(element))
                return false;
        }
        return true;
    }
    return false;
}

MoveType Piece::PawnMove   (int16_t start, int16_t target, const Game& game)
{
    int16_t dir {m_color == Color::WHITE ? -1 : 1}, dx{target - start};
    if (dx == dir * 8 && !game.isPossitionOccupied(target))
    {
        m_hasMoved = true;
        return MoveType::MOVE;
    }
    if ((dx == dir * 7 || dx == dir * 9) && (game.getBoard().at(target).getColor() == getOppositeColor (m_color)))
    {
        m_hasMoved = true;
        return MoveType::MOVE;
    }
    if (dx == dir * 16 && m_hasMoved == false
         && !game.isPossitionOccupied(target)           //check targeted cell
         && !game.isPossitionOccupied(target + dx / 2)) //and one between
    {
        m_hasMoved = true;
        return MoveType::PAWN_PUSH;
    }
    if ((m_color == Color::WHITE && target / 8 == 0) || (m_color == Color::BLACK && target / 8 == 7))
    {
        return MoveType::PROMOTION;
    }
    return MoveType::NOT_VALID;
}
MoveType Piece::RookMove   (int16_t start, int16_t target, const Game& game)
{
    Position s(start), t(target);
    if (((s.m_x == t.m_x) || (s.m_y == t.m_y)) //If one of the coordinates is the same
        && (checkLine(start, target, game)))   //AND if the line between is empty
    {
        m_hasMoved = true;
        return MoveType::MOVE;
    }
    return MoveType::NOT_VALID;
}
MoveType Piece::KnightMove (int16_t start, int16_t target)
{
    int16_t dx {abs(start - target)};
    std::vector <int16_t> correctValues {6, 10, 15, 17};
    for (int16_t entry : correctValues)
    {
        if (dx == entry)
        {
            m_hasMoved = true;
            return MoveType::MOVE;
        }
    }
    return MoveType::NOT_VALID;
}
MoveType Piece::BishopMove (int16_t start, int16_t target, const Game& game)
{
    int16_t dx {abs(start - target)};
    if (dx % 7 == 0 || dx % 9 == 0 &&     //If moving diagonally
        (checkLine(start, target, game))) //AND if the line is empty
    {
        m_hasMoved = true;
        return MoveType::MOVE;
    }
    return MoveType::NOT_VALID;
}
MoveType Piece::QueenMove  (int16_t start, int16_t target, const Game& game)
{
    if (RookMove(start, target, game) == MoveType::MOVE
        || BishopMove (start, target, game) == MoveType::MOVE)
        return MoveType::MOVE;
    else
        return MoveType::NOT_VALID;
}
MoveType Piece::KingMove   (int16_t start, int16_t target)
{
    int16_t dx {abs(start - target)};
    std::vector <int16_t> correctValues {1, 7, 8, 9};
    for (int16_t entry : correctValues)
    {
        if (dx == entry)
        {
            m_hasMoved = true;
            return MoveType::MOVE;
        }
    }
    if (dx == 2)    //castling
    {

        return MoveType::CASTLING;
    }
    return MoveType::NOT_VALID;
}
MoveType Piece::isMoveLegal(const Position& s, const Position& t, Game& game)
{
    if (s == t)
        return MoveType::NOT_VALID;
    int16_t start {positionToIndex(s)}, target{positionToIndex(t)};
    //Check if target square has piece of the same color
    if (game.getBoard().at(start).getColor() == game.getBoard().at(target).getColor())
        return MoveType::NOT_VALID;

    char piece_type{toupper(m_type)};
    switch (piece_type)
    {
        case 'P': return PawnMove   (start, target, game);
        case 'N': return KnightMove (start, target);
        case 'K': return KingMove   (start, target);
        case 'R': return RookMove   (start, target, game);
        case 'B': return BishopMove (start, target, game);
        case 'Q': return QueenMove  (start, target, game);
        default : return MoveType::NOT_VALID;
    }
}

