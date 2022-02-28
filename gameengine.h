#pragma once
#include "includes.h"

#include <memory>
#include <vector>

//One square on board will be made of CELLS width and half CELLS(rounded up) height of characters
//For CELLS = 5 it is 5 characters across and 3 character high
//  |_____|
//  |__Q__|
//  |_____|
//If CELLS is less than 1 board will not print
constexpr int32_t CELLS{5};

class Piece;
class Gameboard
{
    std::unique_ptr<Piece> m_board[8][8];

    void PrintColumnSymbols();
    void PrintLine(bool whiteFirst, int rowNumber);

public:
    Gameboard();
    ~Gameboard();
    void Initialize();
    void PrintBoard();
    Piece *getChesspiece(Position pos);
    void setChesspiece(std::unique_ptr<Piece>upPointer, Position pos);
    void moveChesspiece(Position from, Position to);
    void swapChesspiece(Position pos);
    bool isPossitionOccupied(Position pos);
};

class Player
{
    Color m_playerColor;
public:
    Player(Color color): m_playerColor(color) {}
    ~Player() {}
    Color getPlayerColor();
};

class Game
{
    Gameboard m_board;
    bool m_hasGameEnded         {false};
    Player m_firstPlayer        {Color::WHITE};
    Player m_secondPlayer       {Color::BLACK};
    Player* m_activePlayer      {&m_firstPlayer};
    Player* m_inactivePlayer    {&m_secondPlayer};
public:
    Game() {}
    Gameboard& getGameboard();
    Color getActivePlayer();
    void swapActivePlayer();
    bool getHasGameEnded();
    bool Make_Move();
};
