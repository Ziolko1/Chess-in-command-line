#include "game.h"
#include <cmath>    //floor, ceil

/*Pieces:
p -> Pawn
r -> Rook
n -> Knight
b -> Bishop
q -> Queen
k -> King

t -> En passaint token
*/
Game::Game()
{
    for (uint32_t i{0}; i<BOARDSIZE * BOARDSIZE; ++i)
    {
        m_board.emplace_back();
    }
    for (int i{0}; i<BOARDSIZE; ++i)
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
void Game::PrintColumnSymbols() const
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

void Game::PrintLine (bool whiteFirst=true, int rowNumber=0) const
{
    std::string output;
    //Preparing row of BOARDSIZE(8) squares for printing
    for (int i{0}; i<BOARDSIZE; ++i)
    {
        //Square is CELLS characters wide
        for (int j{0}; j<CELLS; ++j)
        {
            //We need to swap middle of the square for chess piece symbol
            if(((std::floor(static_cast<float>(CELLS)/2))==j)       //Check for correct column
                && rowNumber!=0                                     //Check for correct row
                && m_board.at(i + (BOARDSIZE - rowNumber) * BOARDSIZE).getColor() != Color::EMPTY)
            {
                output += m_board.at(i + (BOARDSIZE - rowNumber) * BOARDSIZE).getType();
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
        output+=' ';
        output+=('0'+rowNumber);
    }
    std::cout << output << '\n';
}

void Game::printBoard() const
{
    //First - column symbols to guide players
    Game::PrintColumnSymbols();
    //Because we can't print on line that was put already on the screen
    //we have to use functions that will do row of cells at a time
    //Printing 8 columns
    for (int i{0}; i<BOARDSIZE; ++i)
    {
        //Square is half CELLS high
        for (int j{0}; j<(std::ceil(static_cast<float>(CELLS)/2)); ++j)
        {
            //If this is middle row we add a row number to the arguments
            if((std::floor(static_cast<float>(CELLS)/4))==j)
                Game::PrintLine(i%2, BOARDSIZE-i);
            else
                Game::PrintLine(i%2);
        }
    }
}

void Game::printInfo() const
{
    if (m_activePlayer == Color::WHITE)
        std::cout << "Your pieces are white. "
        << "White pieces are represented with BIG LETTERS.\n";
    else
        std::cout << "Your pieces are black. "
        << "Black pieces are represented with small letters.\n";
}

bool Game::play()
{

}

bool Game::oneTurn()
{
    bool invalidMove{true};
    while (invalidMove)
    {
        std::vector<int16_t> oneMove {getMove()};
        Piece dummy {m_board.at(oneMove.at(1))};
        m_board.at(oneMove.at(1)) = m_board.at(oneMove.at(0));
        m_board.at(oneMove.at(0)) = Piece();

        //Find and check if King is not endangered by this move
        int16_t kingPosition;
        for (int16_t i{0}; i<m_board.size(); ++i)
        {
            if (toupper(m_board.at(i).getType()) == 'K' && m_board.at(i).getColor() == m_activePlayer)
            {
                kingPosition = i;
                i = m_board.size();
            }
        }
        if (isPositionInDanger(kingPosition))
        {
            std::cout << "This move puts your king in danger!\n";
            m_board.at(oneMove.at(0)) = m_board.at(oneMove.at(0));
            m_board.at(oneMove.at(1)) = dummy;
            continue;
        }
        else
        {
            m_activePlayer = getOppositeColor(m_activePlayer);
            invalidMove = false;
        }
    }
}

std::vector <int16_t> Game::getMove() const
{
    while (true)
    {
        printBoard();
        printInfo();
        Position start {ReadInput("Enter starting position (ie. B1): ")};
        if (m_board.at(positionToIndex(start)).getColor() != m_activePlayer)
        {
            std::cout << "That is not your piece!\n";
            continue;
        }
        Position target {ReadInput("Enter target position (ie. C3): ")};
        MoveType movePrototype {m_board.at(positionToIndex(start)).isMoveLegal(start, target, *this)};
        if (movePrototype == MoveType::NOT_VALID)
        {
            std::cout << "That move is not valid!\n";
            continue;
        }
        return {positionToIndex(start), positionToIndex(target)};
    }
}
bool Game::isPositionInDanger(int16_t target) const
{
    Color x {getOppositeColor(m_board.at(target).getColor())};
    for (int16_t i{0}; i<m_board.size(); ++i)
        if (m_board.at(i).getColor() == x
            && m_board.at(i).isMoveLegal(i, target, *this) != MoveType::NOT_VALID)
            return true;

    return false;
}
bool Game::isPossitionOccupied(int16_t target) const
{
    return m_board.at(target).getColor() == Color::EMPTY ? false : true;
}
bool Game::isReachingLastRank(int16_t start, int16_t target) const
{

    return ((m_board.at(start).getColor() == Color::WHITE && target / 8 == 0)
         || (m_board.at(start).getColor() == Color::BLACK && target / 8 == 7));
}

const std::vector<Piece>& Game::getBoard() const
{
    return m_board;
}
