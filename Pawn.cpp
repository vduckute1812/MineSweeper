#include "Pawn.h"
#include "BoardWnd.h"

Pawn::Pawn(Alliance pieceAlliance, u32 position, QWidget*): Piece(PieceType::PAWN, pieceAlliance, position)
{
}

bool Pawn::isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return false;
}

bool Pawn::isEightColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return false;
}

std::vector<Move *> Pawn::calculateLegalMove(const BoardConfig board) const
{
    return std::vector<Move *>();
}

