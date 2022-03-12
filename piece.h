#pragma once
#include "includes.h"
#include "game.h"

class Game;
class Piece
{
    char m_type;
    Color m_color;
    bool m_hasMoved{false};

    bool checkLine  (int16_t start, int16_t target, const Game& game) const;
    MoveType PawnMove   (int16_t start, int16_t target, const Game& game) const;
    MoveType KnightMove (int16_t start, int16_t target) const;
    MoveType KingMove   (int16_t start, int16_t target, const Game& game) const;
    MoveType RookMove   (int16_t start, int16_t target, const Game& game) const;
    MoveType BishopMove (int16_t start, int16_t target, const Game& game) const;
    MoveType QueenMove  (int16_t start, int16_t target, const Game& game) const;
public:
    Piece();
    Piece(char t, Color c);
    void setPiece(char t, Color c);
    void setMoved();
    bool getMoved() const;
    char getType() const;
    Color getColor() const;
    MoveType isMoveLegal(int16_t start, int16_t target, const Game& game) const;
    MoveType isMoveLegal(const Position& start, const Position& target, const Game& game) const;
};

