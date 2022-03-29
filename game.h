#pragma once
#include "includes.h"
#include "piece.h"

constexpr uint8_t WHITE_SQUARE {0xDB};
constexpr uint8_t BLACK_SQUARE {0xFF};
constexpr uint8_t EMPTY_SQUARE {0x20};

//Board is square of 8x8 cells, no need for separate height and width variables
constexpr int16_t BOARDSIZE{8};

//One square on board will be made of CELLS width and half CELLS(rounded up) height of characters
//For CELLS = 5 it is 5 characters across and 3 character high. For best results keep odd.
//  |_____|
//  |__Q__|
//  |_____|
constexpr int16_t CELLS{5};

struct SingleMove;
class Piece;
class Game
{
    std::vector<Piece> m_board;
    Color m_activePlayer{Color::WHITE};
    int16_t m_activePlayerKingPosition {60};

    void PrintColumnSymbols() const;
    void PrintLine(bool whiteFirst, int rowNumber) const;
public:
    Game();
    bool play();
    bool oneTurn();
    void swapPlayer();
    void printBoard() const;
    void printInfo() const;

    bool isPossitionOccupied(int16_t target) const;
    bool isPositionInDanger(int16_t target) const;
    bool isColliding(const SingleMove& s) const;
    bool isLineEmpty(const SingleMove& s) const;
    bool isReachingLastRank(const SingleMove& s) const;
    SingleMove getMove() const;
    const std::vector<Piece>& getBoard() const;
};
