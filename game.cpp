#include "game.h"
#include <cmath>    //floor, ceil

Game::Game()
{
    m_board.reserve(64);
    for (uint32_t i{0}; i<64; ++i)
    {
        m_board.emplace_back();
    }
    for (int i{0}; i<8; ++i)
    {
        m_board.at(8+i) .setPiece('p',Color::BLACK);
        m_board.at(48+i).setPiece('P',Color::WHITE);
    }
    m_board.at(0).setPiece('r',Color::BLACK);
    m_board.at(1).setPiece('n',Color::BLACK);
    m_board.at(2).setPiece('b',Color::BLACK);
    m_board.at(3).setPiece('q',Color::BLACK);
    m_board.at(4).setPiece('k',Color::BLACK);
    m_board.at(5).setPiece('b',Color::BLACK);
    m_board.at(6).setPiece('n',Color::BLACK);
    m_board.at(7).setPiece('r',Color::BLACK);

    m_board.at(56).setPiece('R',Color::WHITE);
    m_board.at(57).setPiece('N',Color::WHITE);
    m_board.at(58).setPiece('B',Color::WHITE);
    m_board.at(59).setPiece('Q',Color::WHITE);
    m_board.at(60).setPiece('K',Color::WHITE);
    m_board.at(61).setPiece('B',Color::WHITE);
    m_board.at(62).setPiece('N',Color::WHITE);
    m_board.at(63).setPiece('R',Color::WHITE);
}
void Game::PrintColumnSymbols()
{
    std::string output;
    //Before first column symbol we need to add half square of spacing
    for (int i{0}; i<CELLS/2; ++i)
    {
        output+=' ';
    }
    //After first each symbol is CELLS-1(symbol also takes space) apart from each other
    for (int i{0}; i<BOARDSIZE; ++i)
    {
        output+=('A'+i);
        for (int i{1}; i<CELLS; ++i)
        {
            output+=' ';
        }
    }
    output+="\n\n";
    std::cout << output;
}

void Game::PrintLine (bool whiteFirst=true, int rowNumber=0)
{
    std::string output;
    //Preparing row of BOARDSIZE(8) squares for printing
    for (int i{0}; i<BOARDSIZE; ++i)
    {
        //Square is CELLS characters wide
        for (int j{0}; j<CELLS; ++j)
        {
            //We need to swap middle of the square for chess piece symbol
            if(((std::floor(static_cast<float>(CELLS)/2))==j)             //Check for correct column
                    &&(rowNumber!=0))                                     //Check for correct row
            {
                output += m_board.at(PositionToIndex({i+'A', rowNumber+'0'})).getType();
            }
            else
            {
                //Filling rest of the space on gameboard
                if (i%2==whiteFirst)
                    output+=static_cast<char>(WHITE_SQUARE);
                else
                    output+=static_cast<char>(BLACK_SQUARE);
            }
        }
    }

    //After full line we can add which row on board was it
    if (rowNumber!=0)
    {
        output+="\t";
        output+=('0'+rowNumber);
    }
    std::cout << output << '\n';
}

void Game::PrintBoard ()
{
    //First - column symbols for player checking
    Game::PrintColumnSymbols();

    //Because we can't print on line that was put already on the screen
    //we have to use functions that will do row of cells at a time
    //Printing 8 columns
    for (int i{0}; i<BOARDSIZE; ++i)
    {
        //Square is half CELLS high
        for (int j{0}; j<(std::ceil(static_cast<float>(CELLS)/2)); ++j)
        {
            //If this is middle row we add number of it to the arguments (chess notation)
            if((std::floor(static_cast<float>(CELLS)/4))==j)
                Game::PrintLine(i%2, BOARDSIZE-i);
            else
                Game::PrintLine(i%2);
        }
    }
}
