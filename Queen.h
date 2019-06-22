#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen:public Piece
{
public:
    Queen(Alliance pieceAlliance, u32 piecePos = 0, QWidget *parent = nullptr);
    virtual ~Queen();

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;

    virtual bool isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;

    virtual bool isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

};

#endif
