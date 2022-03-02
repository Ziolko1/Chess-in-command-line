#pragma once
#include "includes.h"
#include "game.h"

class Game;
class Piece
{
    char m_type;
    Color m_color;
    bool m_hasMoved{false};

    bool PawnMove   (int16_t start, int16_t target);
    bool KnightMove (int16_t start, int16_t target);
    bool KingMove   (int16_t start, int16_t target);
    bool RookMove   (int16_t start, int16_t target, const Game& game);
    bool BishopMove (int16_t start, int16_t target, const Game& game);
    bool QueenMove  (int16_t start, int16_t target, const Game& game);
public:
    Piece () : m_type(' '), m_color(Color::MAX_VALUE) {}
    Piece (char t, Color c) : m_type(t), m_color(c) {}
    void setPiece(char t, Color c);
    char getType() const;
    Color getColor() const;
    bool isMoveLegal(const Position& start, const Position& target, const Game& game);
};
