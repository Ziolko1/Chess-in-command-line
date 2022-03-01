#include "piece.h"

void Piece::setPiece(char t, Color c)
{
    m_type = t;
    m_color = c;
}

char Piece::getType()
{
    return m_type;
}
