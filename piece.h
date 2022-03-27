#pragma once
#include "includes.h"
#include "game.h"

class Game;
class Piece
{
    char m_type;
    Color m_color;
    bool m_hasMoved{false};

    MoveType PawnMove   (int16_t start, int16_t target) const;
    MoveType KnightMove (int16_t start, int16_t target) const;
    MoveType KingMove   (int16_t start, int16_t target) const;
    MoveType RookMove   (int16_t start, int16_t target) const;
    MoveType BishopMove (int16_t start, int16_t target) const;
    MoveType QueenMove  (int16_t start, int16_t target) const;
public:
    Piece();
    Piece(char t, Color c);
    bool operator== (const Piece& p);
    void setPiece(char t, Color c);
    void setMoved();
    bool getMoved() const;
    char getType() const;
    Color getColor() const;
    MoveType isMoveLegal(int16_t start, int16_t target) const;
    MoveType isMoveLegal(const Position& start, const Position& target) const;
};

