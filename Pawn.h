#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class BoardConfig;
class Pawn :public Piece
{
public:
    Pawn(Alliance pieceAlliance, u32 position, QWidget *parent = nullptr);

    virtual bool isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;

};

#endif // PAWN_H
