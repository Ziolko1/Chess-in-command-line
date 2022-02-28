#include "piece.h"
#include "gameengine.h"

#include <math.h>
#include <vector>
#include <iostream>

char Piece::getPieceSymbol()
{
    return m_pieceSymbol;
}
Color Piece::getPieceColor()
{
    return m_pieceColor;
}
Position Piece::getPiecePosition()
{
    return m_piecePosition;
}
void Piece::setPiecePosition(Position targetPosition)
{
    m_piecePosition = targetPosition;
}

bool Piece::checkLine(Gameboard& board, Position targetPosition)
{
    //std::cout << "CALLED CHECK LINE\n";
    //check if line is straight - horizontal, vertical or diagonal
    //if horizontal or vertical only one coordinate will change     (queen, rook)
    //if vertical both coordinates have to change equal amount      (queen, bishop)
    //we dont have to check current piece position and target - these will be resolved by caller
    int changeX {getPiecePosition().m_x - targetPosition.m_x};
    int changeY {getPiecePosition().m_y - targetPosition.m_y};

    if ((changeX!=0 && changeY==0) || (changeX==0 && changeY!=0) || (abs(changeX)==abs(changeY)))
    {
        std::vector<Position> vPos;
        vPos.reserve(6);    //We dont need more than 6 entries

        while ((changeX !=0) || (changeY!=0))
        {
            //we add position to vector before (in/de)creasing change to skip starting position
            if (!((getPiecePosition().m_x-changeX==targetPosition.m_x)      //this check skips targetPosition
                    &&(getPiecePosition().m_y-changeY==targetPosition.m_y)))
                vPos.emplace_back(Position (getPiecePosition().m_x-changeX,getPiecePosition().m_y-changeY));

            if (changeX)
                (changeX>0 ? --changeX : ++changeX);
            if (changeY)
                (changeY>0 ? --changeY : ++changeY);
        }
        for (auto const &elements : vPos)
        {
            if (board.isPossitionOccupied(elements))
                return false;
        }
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Piece classes implementation////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Pawn::Capture(Gameboard& board, Position targetPosition)
{
    std::cout << "Called Pawn Capture!\n";
    if (getPieceColor()==Color::WHITE)
    {
        if ((board.getChesspiece(targetPosition)->getPieceColor()==Color::BLACK)&&  // check for black pieces on target square
                (targetPosition.m_x-getPiecePosition().m_x==-1)&&       // check if move puts piece one square in front
                (abs(targetPosition.m_y-getPiecePosition().m_y)==1))    // check if move puts piece on square to left or right to origin
        {
            hasMoved=true;
            return true;
        }
    }
    else    //Pawn is black
    {
        if ((board.getChesspiece(targetPosition)->getPieceColor()==Color::WHITE)&& // check for white pieces on target square
                (targetPosition.m_x-getPiecePosition().m_x==1)&&         // check if move puts piece one square in front
                (abs(targetPosition.m_y-getPiecePosition().m_y)==1))     // check if move puts piece on square to left or right to origin
        {
            hasMoved=true;
            return true;
        }
    }
    return false;
}
bool Pawn::Movement(Gameboard& board, Position targetPosition)
{
    std::cout << "Called Pawn Movement!\n";
    if (getPieceColor()==Color::WHITE)
    {
        if ((targetPosition.m_y==getPiecePosition().m_y)&&          //Pawns cant move to sides
                ((targetPosition.m_x-getPiecePosition().m_x==-1)||  //Move one square forward (upwards) OR
                 ((targetPosition.m_x-getPiecePosition().m_x==-2)&& //Move two squares forward (upwards) if
                  (hasMoved==false))))                              //pawn hasnt moved yet
        {
            board.moveChesspiece(getPiecePosition(), targetPosition);
            hasMoved=true;
            return true;
        }
    }
    else    //Pawn is black
        if ((targetPosition.m_y==getPiecePosition().m_y)&&          //Pawns cant move to sides
                ((targetPosition.m_x-getPiecePosition().m_x==1)||   //Move one square forward (downwards) OR
                 ((targetPosition.m_x-getPiecePosition().m_x==2)&&  //Move two squares forward (downwards) if
                  (hasMoved==false))))                              //pawn hasnt moved yet
        {
            board.moveChesspiece(getPiecePosition(), targetPosition);
            hasMoved=true;
            return true;
        }
        std::cout << "Pawn Movement FAILED!\n";
    return false;
}

bool Rook::Capture(Gameboard& board, Position targetPosition)
{
    std::cout << "Called Rook Capture!\n";
    //Check if move is legal - only one coordinate may change
    int moveOnX {targetPosition.m_x-getPiecePosition().m_x};
    int moveOnY {targetPosition.m_y-getPiecePosition().m_y};
    if ((moveOnX&&(!moveOnY)) || ((!moveOnX)&&moveOnY))
    {
        //Check if the way to target is clear AND target location is occupied
        if ((checkLine(board, targetPosition))&&board.isPossitionOccupied(targetPosition))
        {
            //If target is not on your team we can capture
            if (board.getChesspiece(targetPosition)->getPieceColor()!=getPieceColor())
            {
                hasMoved = true;
                return true;
            }
        }
    }
    return false;
}
bool Rook::Movement(Gameboard& board, Position targetPosition)
{
    std::cout << "Called Rook Movement!\n";
    //Check if move is legal - only one coordinate may change
    int moveOnX {targetPosition.m_x-getPiecePosition().m_x};
    int moveOnY {targetPosition.m_y-getPiecePosition().m_y};
    if ((moveOnX&&(!moveOnY)) || ((!moveOnX)&&moveOnY))
    {
        //Check if the way to target is clear AND target location is NOT occupied
        if ((checkLine(board, targetPosition))&&(!board.isPossitionOccupied(targetPosition)))
        {
            hasMoved = true;
            return true;
        }
    }
    return false;
}

bool Knight::Capture(Gameboard& board, Position targetPosition)
{
    //Knight can jump through allies and enemies, we need only to check if it moves correctly
    int moveOnX {abs(targetPosition.m_x-getPiecePosition().m_x)};
    int moveOnY {abs(targetPosition.m_y-getPiecePosition().m_y)};
    if (((moveOnX == 2) && (moveOnY == 1)) || ((moveOnX == 1) && (moveOnY == 2)))
    {
        //Check if target location is occupied
        if (board.isPossitionOccupied(targetPosition))
        {
            //If target is not on our team we can capture
            if (board.getChesspiece(targetPosition)->getPieceColor()!=getPieceColor())
                return true;
        }
    }
    return false;
}
bool Knight::Movement(Gameboard& board, Position targetPosition)
{
    //Knight can jump through allies and enemies, we need only to check if it moves correctly
    int moveOnX {abs(targetPosition.m_x-getPiecePosition().m_x)};
    int moveOnY {abs(targetPosition.m_y-getPiecePosition().m_y)};
    if (((moveOnX == 2) && (moveOnY == 1)) || ((moveOnX == 1) && (moveOnY == 2)))
    {
        //Check if target location is NOT occupied
        if (!board.isPossitionOccupied(targetPosition))
            return true;
    }
    return false;
}

bool Bishop::Capture(Gameboard& board, Position targetPosition)
{
    int moveOnX {abs(targetPosition.m_x-getPiecePosition().m_x)};
    int moveOnY {abs(targetPosition.m_y-getPiecePosition().m_y)};
    //Check if move is legal - both coordinates must change equally
    if (moveOnX == moveOnY)
    {
        //Check if the way to target is clear AND target location is occupied
        if ((checkLine(board, targetPosition))&&board.isPossitionOccupied(targetPosition))
        {
            //If target is not on our team we can capture
            if (board.getChesspiece(targetPosition)->getPieceColor()!=getPieceColor())
                return true;
        }
    }
    return false;
}
bool Bishop::Movement(Gameboard& board, Position targetPosition)
{
    //Check if move is legal - only on one axis may change
    int moveOnX {abs(targetPosition.m_x-getPiecePosition().m_x)};
    int moveOnY {abs(targetPosition.m_y-getPiecePosition().m_y)};
    if ((moveOnX&&(!moveOnY)) || ((!moveOnX)&&moveOnY))
    {
        //Check if the way to target is clear AND target location is NOT occupied
        if ((checkLine(board, targetPosition))&&(!board.isPossitionOccupied(targetPosition)))
            return true;
    }
    return false;
}

bool Queen::Capture(Gameboard& board, Position targetPosition)
{
    //Because Queen can move on horizontal, vertical and diagonal lines checkLine is only check we need for illegal moves
    //Check if the way to target is clear AND target location is occupied
    if ((checkLine(board, targetPosition))&&board.isPossitionOccupied(targetPosition))
    {
        //If target is not on our team we can capture
        if (board.getChesspiece(targetPosition)->getPieceColor()!=getPieceColor())
            return true;
    }
    return false;
}
bool Queen::Movement(Gameboard& board, Position targetPosition)
{
    //Because Queen can move on horizontal, vertical and diagonal lines checkLine is only check we need for illegal moves
    //Check if the way to target is clear AND target location is NOT occupied
    if ((checkLine(board, targetPosition))&&(!board.isPossitionOccupied(targetPosition)))
    {
        return true;
    }
    return false;
}

bool King::Capture(Gameboard& board, Position targetPosition)
{
    int moveOnX {abs(targetPosition.m_x-getPiecePosition().m_x)};
    int moveOnY {abs(targetPosition.m_y-getPiecePosition().m_y)};
    //King can move 1 square in every direction
    if ((moveOnX<2)&&(moveOnY<2))
    {
        return true;
    }
    return false;
}
bool King::Movement(Gameboard& board, Position targetPosition)
{
    int moveOnX {abs(targetPosition.m_x-getPiecePosition().m_x)};
    int moveOnY {abs(targetPosition.m_y-getPiecePosition().m_y)};
    //King can move 1 square in every direction
    if ((moveOnX<2)&&(moveOnY<2))
    {
        return true;
    }
    return false;
}

bool King::Endanger(Gameboard& board, Position targetPosition)
{
//This function checks if move puts king in danger
    for (int i{0};i<8;++i)
    {
        for (int j{0};j<8;++j)
        {
            if (board.isPossitionOccupied({i,j}))
            {
                //Check if position on board is occupied by enemy team
                if (board.getChesspiece({i,j})->getPieceColor()!=getPieceColor())
                {
                    //Checks if chosen position can capture Kings position
                    if (board.getChesspiece({i,j})-> Capture(board,getPiecePosition()))
                        return true;
                }
            }
        }
    }
    return false;
}
