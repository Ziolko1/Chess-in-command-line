#include "includes.h"
#include "game.h"
#include "piece.h"

constexpr bool DEBUG {1};

int main()
{
    if (DEBUG)
        tests();

    Game game;
    for (int i{0}; i<game.getBoard().size(); ++i)
    {
        if (game.getBoard().at(i).getColor() == Color::WHITE)
            std::cout << "Cell: " << i << "is WHITE!\n";
        if (game.getBoard().at(i).getColor() == Color::EMPTY)
            std::cout << "Cell: " << i << "is EMPTY!\n";
        if (game.getBoard().at(i).getColor() == Color::BLACK)
            std::cout << "Cell: " << i << "is BLACK!\n";
    }

    game.play();
    return 0;
}
