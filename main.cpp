#include "includes.h"
#include "piece.h"
#include "gameengine.h"

#include <iostream>
int main()
{
    Game game;
    while (!game.getHasGameEnded())
    {
        game.getGameboard().PrintBoard();
        std::cout << "Active player: ";
        game.getActivePlayer() == Color::WHITE ?
                    std::cout << "WHITE (BIG LETTERS)\n" :
                    std::cout << "BLACK (small letters)\n";
        while(game.Make_Move())
        {

            game.getGameboard().PrintBoard();
            game.swapActivePlayer();
        }
    }

    /*Gameboard board;
    board.moveChesspiece({0,0},{3,3});
    board.PrintBoard();
    for (int i=0; i<8; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            std::cout << board.getChesspiece({3,3})->checkLine(board, {i,j}) << ' ';
        }
        std::cout << '\n';
    }

    if(board.isPossitionOccupied({0,0}))
    board.moveChesspiece({0,0},{0,6});

    board.PrintBoard();*/

    return 0;
}
