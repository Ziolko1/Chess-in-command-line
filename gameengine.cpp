#include "piece.h"
#include "gameengine.h"
#include "includes.h"

#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::cin;

//Uniform initialization didn't work on my compiler, char is implemented as signed
//not accepting values higher than 127 if uniform initialization is used
constexpr char WHITE_SQUARE=0xDB;
constexpr char BLACK_SQUARE=0xFF;
constexpr char EMPTY_SQUARE=0x20;

//Board is square of 8x8 cells, no need for separate height and width variables
constexpr int BOARDSIZE{8};

Gameboard::Gameboard()
{
    //To distinguish pawn colors white uses uppercase and black uses lowercase
    //fill row second from top with black pawns
    for (int j=0; j<8; j++)
    {
        m_board[1][j]=std::make_unique<Pawn>(Color::BLACK, 'p',1,j);
    }
    //fill row second to last with white pawns
    for (int j=0; j<8; j++)
    {
        m_board[6][j]=std::make_unique<Pawn>(Color::WHITE, 'P',6,j);
    }
    //fill black rooks
    m_board[0][0]=std::make_unique<Rook>(Color::BLACK, 'r',0,0);
    m_board[0][7]=std::make_unique<Rook>(Color::BLACK, 'r',0,7);
    //fill white rooks
    m_board[7][0]=std::make_unique<Rook>(Color::WHITE, 'R',7,0);
    m_board[7][7]=std::make_unique<Rook>(Color::WHITE, 'R',7,7);
    //fill black knights
    m_board[0][1]=std::make_unique<Knight>(Color::BLACK, 'n',0,1);
    m_board[0][6]=std::make_unique<Knight>(Color::BLACK, 'n',0,6);
    //fill white knights
    m_board[7][1]=std::make_unique<Knight>(Color::WHITE, 'N',7,1);
    m_board[7][6]=std::make_unique<Knight>(Color::WHITE, 'N',7,6);
    //fill black bishops
    m_board[0][2]=std::make_unique<Bishop>(Color::BLACK, 'b',0,2);
    m_board[0][5]=std::make_unique<Bishop>(Color::BLACK, 'b',0,5);
    //fill white bishops
    m_board[7][2]=std::make_unique<Bishop>(Color::WHITE, 'B',7,2);
    m_board[7][5]=std::make_unique<Bishop>(Color::WHITE, 'B',7,5);
    //fill queens
    m_board[0][3]=std::make_unique<Queen>(Color::BLACK, 'q',0,3);
    m_board[7][3]=std::make_unique<Queen>(Color::WHITE, 'Q',7,3);
    //fill kings
    m_board[0][4]=std::make_unique<King>(Color::BLACK, 'k',0,4);
    m_board[7][4]=std::make_unique<King>(Color::WHITE, 'K',7,4);
    //filling rest of the board with dangling pointers for move semantics
    for (int i=2; i<6; ++i)
    {
        for (int j=0; j<8; ++j)
        {
            m_board[i][j]=std::unique_ptr<Piece>();
        }
    }
}

Gameboard::~Gameboard() {}
void Gameboard::PrintColumnSymbols()
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

void Gameboard::PrintLine (bool whiteFirst=true, int rowNumber=0)
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
                    &&(rowNumber!=0)                                      //Check for correct row
                    &&(getChesspiece({(BOARDSIZE-rowNumber),i})!=nullptr))  //Check for piece on the current spot
            {
                output+=getChesspiece({(BOARDSIZE-rowNumber),i})->getPieceSymbol();
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

void Gameboard::PrintBoard ()
{
    //First - column symbols for player checking
    Gameboard::PrintColumnSymbols();

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
                Gameboard::PrintLine(i%2, BOARDSIZE-i);
            else
                Gameboard::PrintLine(i%2);
        }
    }
}

Piece* Gameboard::getChesspiece(Position pos)
{
    return m_board[pos.m_x][pos.m_y].get();
}
void Gameboard::setChesspiece(std::unique_ptr<Piece> upPointer, Position pos)
{
    m_board[pos.m_x][pos.m_y] = std::move(upPointer);
}
void Gameboard::moveChesspiece(Position from, Position to)
{
    std::cout << "Move Chesspiece called with: " << from << to << '\n';
    getChesspiece({from.m_x,from.m_y})->setPiecePosition({to.m_x,to.m_y});
    m_board[to.m_y][to.m_x] = std::move(m_board[from.m_y][from.m_x]);
}
bool Gameboard::isPossitionOccupied(Position pos)
{
    return getChesspiece(pos);
}

/*void Gameboard::deleteChesspiece(Position pos)
{

}*/

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Player class implementation////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

Color Player::getPlayerColor()
{
    return m_playerColor;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Game class implementation/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

Gameboard& Game::getGameboard()
{
    return m_board;
}
bool Game::getHasGameEnded()
{
    return m_hasGameEnded;
}

bool Game::Make_Move()
{
    Position start = ReadInput("Enter starting position (ie. B8): ");
    std::cout << start.m_x << ',' << start.m_y << '\n';
    if (m_board.getChesspiece(start) == nullptr)
    {
        std::cout << "There is no piece on this square!\n";
        return false;
    }
    if (m_board.getChesspiece(start)->getPieceColor() != m_activePlayer->getPlayerColor())
    {
        std::cout << "This piece is not yours!\n";
        return false;
    }
    Position end = ReadInput("Enter target position (ie. A7): ");
    std::cout << end.m_x << ',' << end.m_y << '\n';
    if (!m_board.getChesspiece(end))
    {
        std::cout << "NULLPTR AHEAD\n";
        return m_board.getChesspiece(start)->Movement(m_board, end);
    }
    if (m_board.getChesspiece(start)->getPieceColor() != m_activePlayer->getPlayerColor())
    {
        std::cout << "ENEMY AHEAD\n";
        return m_board.getChesspiece(start)->Capture(m_board, end);
    }
    return false;
}
void Game::swapActivePlayer()
{
    std::swap(m_activePlayer, m_inactivePlayer);
}
Color Game::getActivePlayer()
{
    return m_activePlayer->getPlayerColor();
}
