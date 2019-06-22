#include "Queen.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"
#include "BoardWnd.h"

const static int QUEEN_CANDIDATE_MOVE_COORDINATE[] = { -NUM_TILES_PER_COL-1,
                                                       -NUM_TILES_PER_COL,
                                                       -NUM_TILES_PER_COL+1,
                                                       -1, 1,
                                                       NUM_TILES_PER_COL-1,
                                                       NUM_TILES_PER_COL,
                                                       NUM_TILES_PER_COL+1 };

Queen::Queen(Alliance pieceAlliance,u32 piecePos, QWidget *parent) :
    Piece(PieceType::QUEEN, pieceAlliance, piecePos, parent)
{
}

Queen::~Queen()
{
}

bool Queen::isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition)
            && (candidateOffset == -1 || candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool Queen::isEightColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition)
            && (candidateOffset == 1 || candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection Queen::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;

    for (int candidateCoordinationOffset : QUEEN_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + candidateCoordinationOffset;

        while (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)
                || isEightColumnExclusion(this->m_piecePosition, candidateCoordinationOffset)){
                break;
            }

            u32 candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            Piece* destPiece = BoardWnd::GetInstance()->GetPieceOnBoard(board, candidateDestCoord);

            if (!BoardWnd::GetInstance()->IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance(this->GetAlliance(), destPiece->GetAlliance()))
            {
                legalMoves.push_back(new Move(board, this, destPiece, candidateDestCoord));
            }
            else // Stop by Enemy or Alliance
            {
                break;
            }

            if (BoardWnd::GetInstance()->IsTileOccupied(board, candidateDestCoord))
            {
                break;
            }

            if (candidateCoordinationOffset != NUM_TILES_PER_COL && candidateCoordinationOffset != -NUM_TILES_PER_COL)
            {
                if (BoardUntils::IsNumColumn(1, candidateDestCoord)
                    || BoardUntils::IsNumColumn(NUM_TILES_PER_COL, candidateDestCoord))
                {
                    break;
                }
            }

            candidateDestinationCoordinate += candidateCoordinationOffset;
        }
    }

	return legalMoves;
}
