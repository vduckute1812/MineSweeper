#include "PieceFactory.h"
#include "Rook.h"
#include "Pawn.h"

Piece *PieceFactory::GeneratePiece(QString pieceStr, Alliance pieceType, u32 position)
{
        if(pieceStr == "Rook")          return new Rook(pieceType, position);
//    else if(pieceStr == "Knight")       return new Knight(pieceType, position);
//    else if(pieceStr == "Bishop")       return new Bishop(pieceType, position);
//    else if(pieceStr == "Queen")        return new Queen(pieceType, position);
//    else if(pieceStr == "King")         return new King(pieceType, position);
    else if(pieceStr == "Pawn")         return new Pawn(pieceType, position);

    else return nullptr;
}
