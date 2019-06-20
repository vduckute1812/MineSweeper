#include "Rook.h"
#include "BoardWnd.h"

Rook::Rook(Alliance pieceAlliance, u32 position, QWidget*): Piece(PieceType::ROOK, pieceAlliance, position)
{
}

std::vector<Move*> Rook::calculateLegalMove(const BoardConfig board) const
{
    return std::vector<Move *>();
}

bool Rook::isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return false;
}

bool Rook::isEightColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return false;
}
