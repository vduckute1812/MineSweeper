#ifndef KING_H
#define KING_H

#include "Piece.h"

class King :public Piece
{
public:
    King(Alliance pieceAlliance, u32 piecePos = 0, QWidget *parent = nullptr);
    virtual ~King();

    virtual bool isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;
};

#endif
