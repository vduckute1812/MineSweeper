#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn :public Piece
{
public:
    Pawn(Alliance pieceAlliance, u32 piecePos = 0, QWidget *parent = nullptr);
	~Pawn();

    virtual bool isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board) const;

	int			getDirection() const;
    bool        isPromote() const;
};

#endif
