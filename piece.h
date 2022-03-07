#pragma once
#include "includes.h"
#include "game.h"

class Game;
class Piece
{
    char m_type;
    Color m_color;
    bool m_hasMoved{false};

    bool checkLine  (int16_t start, int16_t target, const Game& game);
    MoveType PawnMove   (int16_t start, int16_t target, const Game& game);
    MoveType KnightMove (int16_t start, int16_t target);
    MoveType KingMove   (int16_t start, int16_t target);
    MoveType RookMove   (int16_t start, int16_t target, const Game& game);
    MoveType BishopMove (int16_t start, int16_t target, const Game& game);
    MoveType QueenMove  (int16_t start, int16_t target, const Game& game);
public:
    Piece () : m_type(' '), m_color(Color::EMPTY) {}
    Piece (char t, Color c) : m_type(t), m_color(c) {}
    void setPiece(char t, Color c);
    char getType() const;
    Color getColor() const;
    MoveType isMoveLegal(const Position& start, const Position& target, const Game& game);
};

