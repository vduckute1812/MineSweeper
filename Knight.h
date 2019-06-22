#ifndef KNIGHT_H
#define KNIGHT_H


#include "Piece.h"

class Knight : public Piece
{
public:

    Knight(Alliance pieceAlliance,u32 piecePosition = 0, QWidget *parent = nullptr);
    virtual ~Knight();
	
    virtual std::vector<Move*> calculateLegalMove(const BoardConfig board)  const;

    virtual bool isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const;
    virtual bool isEightColumnExclusion(u32 currentPosition, int candidateOffset) const;

    bool isSecondColumnExclusion(u32 currentPosition, int candidateOffset) const;
    bool isSeventhColumnExclusion(u32 currentPosition, int candidateOffset) const;

};

#endif
