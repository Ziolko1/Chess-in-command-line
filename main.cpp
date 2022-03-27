#include "includes.h"
#include "game.h"
#include "piece.h"

constexpr bool DEBUG {1};

int main()
{
    if (DEBUG)
        tests();

    Game game;
    game.play();
    return 0;
}
