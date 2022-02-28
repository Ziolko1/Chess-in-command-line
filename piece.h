#pragma once
#include "includes.h"

class Gameboard;
class Piece
{
private:
    Color m_pieceColor;
    char m_pieceSymbol;
    Position m_piecePosition;

public:
    Piece(Color color, char pieceSymbol, int x, int y): m_pieceColor(color), m_pieceSymbol(pieceSymbol), m_piecePosition(x, y) {};
    ~Piece(){};

    char getPieceSymbol();
    Color getPieceColor();
    Position getPiecePosition();
    void setPiecePosition(Position targetPosition);
    bool checkLine(Gameboard& board, Position targetPosition);
    virtual bool Capture(Gameboard& board, Position targetPosition)=0;
    virtual bool Movement(Gameboard& board, Position targetPosition)=0;

};

class Pawn : public Piece
{
    bool hasMoved {false};

public:
    Pawn(Color color, char pieceSymbol, int x, int y): Piece(color, pieceSymbol, x, y) {}
    ~Pawn(){}
    bool Capture(Gameboard& board, Position targetPosition);
    bool Movement(Gameboard& board, Position targetPosition);
};

class Rook : public Piece
{
    bool hasMoved {false};

public:
    Rook(Color color, char pieceSymbol, int x, int y): Piece(color, pieceSymbol, x, y) {}
    ~Rook(){}
    bool Capture(Gameboard& board, Position targetPosition);
    bool Movement(Gameboard& board, Position targetPosition);
};

class Knight : public Piece
{

public:
    Knight(Color color, char pieceSymbol, int x, int y): Piece(color, pieceSymbol, x, y) {}
    ~Knight(){}
    bool Capture(Gameboard& board, Position targetPosition);
    bool Movement(Gameboard& board, Position targetPosition);
};

class Bishop : public Piece
{

public:
    Bishop(Color color, char pieceSymbol, int x, int y): Piece(color, pieceSymbol, x, y) {}
    ~Bishop(){}
    bool Capture(Gameboard& board, Position targetPosition);
    bool Movement(Gameboard& board, Position targetPosition);
};

class Queen : public Piece
{

public:
    Queen(Color color, char pieceSymbol, int x, int y): Piece(color, pieceSymbol, x, y) {}
    ~Queen(){}
    bool Capture(Gameboard& board, Position targetPosition);
    bool Movement(Gameboard& board, Position targetPosition);
};

class King : public Piece
{
    bool hasMoved {false};

public:
    King(Color color, char pieceSymbol, int x, int y): Piece(color, pieceSymbol, x, y) {}
    ~King(){}
    bool Capture(Gameboard& board, Position targetPosition);
    bool Movement(Gameboard& board, Position targetPosition);
    bool Endanger(Gameboard& board, Position targetPosition);
};
