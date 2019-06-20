#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include "Piece.h"

class PieceFactory
{
public:
    static Piece* GeneratePiece(QString pieceStr, Alliance pieceType, u32 position);
};

#endif // PIECEFACTORY_H
