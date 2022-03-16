#include "includes.h"
#include "game.h"
#include "piece.h"

constexpr bool DEBUG {1};

int main()
{
    if (DEBUG)
        tests();

    Game game;
    game.oneTurn();
    game.oneTurn();
    return 0;
}
