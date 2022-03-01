#include "includes.h"
#include "game.h"
#include "piece.h"

constexpr bool DEBUG {1};

int main()
{
    if (DEBUG)
        tests();

    Game game;
    game.PrintBoard();

    return 0;
}
