#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(Alliance pieceAlliance, u32 piecePos = 0, QWidget *parent = nullptr);
    virtual ~Rook();

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;

    virtual bool isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;

    virtual bool isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

};

#endif
