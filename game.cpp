#include "game.h"
#include <cmath>    //floor, ceil

/*Pieces:
p -> Pawn
r -> Rook
n -> Knight
b -> Bishop
q -> Queen
k -> King

t -> Token for en passant
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
const std::vector<Piece>& Game::getBoard() const
{
    return m_board;
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
    while (true)
        oneTurn();
}
void Game::swapPlayer()
{
    m_activePlayer = getOppositeColor(m_activePlayer);
    Piece dummy {'k', m_activePlayer};
    for (int16_t i{0}; i<m_board.size(); ++i)
    {
        if (m_board.at(i) == dummy)
        {
            m_activePlayerKingPosition = i;
            std::cout << "King found on position: " << i << '\n';
            return;
        }
    }
}
bool Game::oneTurn()
{
    while (true)
    {
        printBoard();
        printInfo();
        if (isPositionInDanger(m_activePlayerKingPosition))
        {
            std::cout << "Your king is in check!\n";
        }
        SingleMove oneMove {getMove()};

        Piece dummy {m_board.at(oneMove.target)};
        m_board.at(oneMove.target) = m_board.at(oneMove.start);
        m_board.at(oneMove.start) = Piece();

        if (isPositionInDanger(m_activePlayerKingPosition))
        {
            std::cout << "This move puts your king in danger!\n";
            m_board.at(oneMove.start) = m_board.at(oneMove.target);
            m_board.at(oneMove.target) = dummy;
            continue;
        }
        else
        {
            swapPlayer();
            return true;
        }
    }
}

SingleMove Game::getMove() const
{
    while (true)
    {
        int16_t start {positionToIndex(ReadInput("Enter starting position (ie. B1): "))};
        if (m_board.at(start).getColor() != m_activePlayer)
        {
            std::cout << "That is not your piece!\n";
            continue;
        }
        int16_t target {positionToIndex(ReadInput("Enter target position (ie. C3): "))};
        MoveType mType {m_board.at(start).isMoveLegal(start, target)};
        if (mType == MoveType::NOT_VALID)
        {
            std::cout << "This piece can not move in that way!\n";
            continue;
        }
        if (mType == MoveType::CHECK_COLLISION && !isLineEmpty({start, target}))
        {
            std::cout << "There is something in the way!\n";
            continue;
        }
        if (m_board.at(target).getColor() == m_activePlayer)
        {
            std::cout << "You can not capture your own pieces!\n";
            continue;
        }
        return {start, target};
    }
}

bool Game::isPositionInDanger(int16_t target) const
{
    Color x {getOppositeColor(m_activePlayer)};
    for (int16_t i{0}; i<m_board.size(); ++i)
    {
        MoveType mType {m_board.at(i).isMoveLegal({i, target})};
        if (m_board.at(i).getColor() == x
            && mType != MoveType::NOT_VALID
            && (mType == MoveType::CHECK_COLLISION && isLineEmpty({i, target})))
            {
                if (m_board.at(i).getColor() == x)
                    std::cout << "TRUE!";
                std::cout << "Piece " << m_board.at(i).getType() << " at " << i << " puts piece "
                          << m_board.at(target).getType() << " at " << target << " in danger!\n";
                return true;
            }
    }
    return false;
}
bool Game::isPossitionOccupied(int16_t target) const
{
    return m_board.at(target).getColor() == Color::EMPTY ? false : true;
}
bool Game::isReachingLastRank(const SingleMove& s) const
{
    return ((m_board.at(s.start).getColor() == Color::WHITE && s.target / 8 == 0)
         || (m_board.at(s.start).getColor() == Color::BLACK && s.target / 8 == 7));
}

bool Game::isLineEmpty(const SingleMove& s) const
{
    //Check if a straight, horizontal, vertical or diagonal line can be made from provided points
    //If it is horizontal or vertical only one coordinate will change     (queen, rook)
    //If is is diagonal both coordinates have to change equal amount      (queen, bishop)
    //We do not have to check current piece position and target - these will be checked by caller
    int changeX {(s.start - s.target) % 8};
    int changeY {(s.start - s.target) / 8};

    if ((!changeX && changeY) || (changeX && !changeY) || abs(changeX)==abs(changeY))
    {
        while (changeX || changeY)
        {
            //(in/de)crease change before adding position to skip starting position
            if (changeX)
                (changeX>0 ? --changeX : ++changeX);
            if (changeY)
                (changeY>0 ? --changeY : ++changeY);
            //Check to avoid adding target position
            if ((changeX || changeY) && (isPossitionOccupied(s.target + changeX + changeY*8)))
                    return false;
        }
        return true;
    }
    return false;
}
