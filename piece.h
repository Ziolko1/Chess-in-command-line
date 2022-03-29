#pragma once
#include "includes.h"
#include "game.h"

class Game;
class Piece
{
    char m_type;
    Color m_color;
    bool m_hasMoved{false};

    MoveType PawnMove   (const SingleMove& s) const;
    MoveType KnightMove (const SingleMove& s) const;
    MoveType KingMove   (const SingleMove& s) const;
    MoveType RookMove   (const SingleMove& s) const;
    MoveType BishopMove (const SingleMove& s) const;
    MoveType QueenMove  (const SingleMove& s) const;
public:
    Piece();
    Piece(char t, Color c);
    bool operator== (const Piece& p);
    void setPiece(char t, Color c);
    void setMoved();
    bool getMoved() const;
    char getType() const;
    Color getColor() const;
    MoveType isMoveLegal(const SingleMove& s) const;
    MoveType isMoveLegal(const Position& start, const Position& target) const;
};

