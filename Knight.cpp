#include "Knight.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"
#include "BoardWnd.h"

const int KNIGHT_CANDIDATE_MOVE_COORDINATE[] = { -2*NUM_TILES_PER_COL-1,
                                                 -2*NUM_TILES_PER_COL+1,
                                                 -NUM_TILES_PER_COL-2,
                                                 -NUM_TILES_PER_COL+2,
                                                  NUM_TILES_PER_COL-2,
                                                  NUM_TILES_PER_COL+2,
                                                  2*NUM_TILES_PER_COL-1,
                                                  2*NUM_TILES_PER_COL+1 };

Knight::Knight(Alliance pieceAlliance,u32 piecePosition, QWidget *parent) :
    Piece(PieceType::KNIGHT, pieceAlliance, piecePosition, parent)
{
    m_pieceValue = KNIGHT_VALUE;
}

Knight::~Knight()
{
}

bool Knight::isFirstColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition)
            && (candidateOffset == -2*NUM_TILES_PER_COL-1 || candidateOffset == -NUM_TILES_PER_COL-2
             || candidateOffset == NUM_TILES_PER_COL-2 || candidateOffset == 2*NUM_TILES_PER_COL-1);
}

bool Knight::isSecondColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::SECOND, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL-2 || candidateOffset == NUM_TILES_PER_COL-2);
}

bool Knight::isSeventhColumnExclusion(unsigned int currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::NEAR_END_OF_COL, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL+2 || candidateOffset == NUM_TILES_PER_COL+2);
}

bool Knight::isEightColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition)
            &&(candidateOffset == -2*NUM_TILES_PER_COL+1 || candidateOffset == -NUM_TILES_PER_COL+2
            || candidateOffset == NUM_TILES_PER_COL+2  || candidateOffset == 2*NUM_TILES_PER_COL+1);
}

MoveCollection Knight::calculateLegalMove(const BoardConfig board)  const
{
    MoveCollection legalMoves;

    int candidateDestinationCoordinate;	// candidate coordinate

    for (int currentCandidateOffset : KNIGHT_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + currentCandidateOffset;
        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isSecondColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isSeventhColumnExclusion(this->m_piecePosition, currentCandidateOffset)
                || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset))
            {
                continue;
            }

            u32 candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            Piece* destPiece = BoardWnd::GetInstance()->GetPieceOnBoard(board, candidateDestCoord);

            if (!BoardWnd::GetInstance()->IsTileOccupied(board, candidateDestCoord) ||
            !BoardUntils::IsSameAlliance(this->GetAlliance(), destPiece->GetAlliance()))
            {
                legalMoves.push_back(new Move(board, this, destPiece, candidateDestCoord));
            }
        }
    }

	return legalMoves;
}

