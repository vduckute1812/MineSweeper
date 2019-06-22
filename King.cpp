#include "King.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"
#include "BoardWnd.h"

const int KING_CANDIDATE_MOVE_COORDINATE[] = { -NUM_TILES_PER_COL-1,
                                               -NUM_TILES_PER_COL,
                                               -NUM_TILES_PER_COL+1,
                                               -1, 1,
                                                NUM_TILES_PER_COL-1,
                                                NUM_TILES_PER_COL,
                                                NUM_TILES_PER_COL+1 };


King::King(Alliance pieceAlliance, u32 piecePos, QWidget *parent) :
    Piece(PieceType::KING, pieceAlliance, piecePos, parent)
{
    m_pieceValue = KING_VALUE;
}


King::~King()
{
}

bool King::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition) &&
            (candidateOffset == -1 || candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool King::isEightColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition) &&
            (candidateOffset == 1 || candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection King::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;	// candidate coordinate

    for (int currentCandidateOffset : KING_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + currentCandidateOffset;
        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
            {
                continue;
            }

            unsigned int candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            Piece* destPiece = BoardWnd::GetInstance()->GetPieceOnBoard(board, candidateDestCoord);

            if (!BoardWnd::GetInstance()->IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance( this->GetAlliance(), destPiece->GetAlliance()) )
            {
                legalMoves.push_back(new Move(board, this, destPiece, candidateDestCoord));
            }
        }
    }

	return legalMoves;
}
