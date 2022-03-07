#pragma once
#include "includes.h"
#include "piece.h"

//Uniform initialization did not work on my compiler, char is implemented as signed
//It is not accepting values higher than 127 if uniform initialization is used
constexpr char WHITE_SQUARE=0xDB;
constexpr char BLACK_SQUARE=0xFF;
constexpr char EMPTY_SQUARE=0x20;

//Board is square of 8x8 cells, no need for separate height and width variables
constexpr int16_t BOARDSIZE{8};

//One square on board will be made of CELLS width and half CELLS(rounded up) height of characters
//For CELLS = 5 it is 5 characters across and 3 character high. For best results keep odd.
//  |_____|
//  |__Q__|
//  |_____|
constexpr int16_t CELLS{5};

class Piece;
class Game
{
    std::vector<Piece> m_board;

    void PrintColumnSymbols() const;
    void PrintLine(bool whiteFirst, int rowNumber) const;
public:
    Game();
    void PrintBoard() const;
    bool isPossitionOccupied(int16_t target) const;
    const std::vector<Piece>& getBoard() const;
};
