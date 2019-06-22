#include "Pawn.h"
#include "Tile.h"
#include "Move.h"
#include "BoardUntils.h"
#include "BoardWnd.h"

const int PAWN_CANDIDATE_MOVE_COORDINATE[] = { NUM_TILES_PER_COL-1,
                                               NUM_TILES_PER_COL,
                                               NUM_TILES_PER_COL+1,
                                               2*NUM_TILES_PER_COL };

Pawn::Pawn(Alliance pieceAlliance, u32 piecePos, QWidget *parent) :
    Piece(PieceType::PAWN, pieceAlliance, piecePos, parent)
{
}

Pawn::~Pawn()
{
}

bool Pawn::isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::FIRST, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL-1 || candidateOffset == NUM_TILES_PER_COL-1);
}

bool Pawn::isEightColumnExclusion(u32 currentPosition, int candidateOffset) const
{
    return BoardUntils::IsNumColumn(CheckColumn::END_OF_COL, currentPosition)
            && (candidateOffset == -NUM_TILES_PER_COL+1 || candidateOffset == NUM_TILES_PER_COL+1);
}

MoveCollection Pawn::calculateLegalMove(const BoardConfig board) const
{
    MoveCollection legalMoves;
    int candidateDestinationCoordinate;
    for (int currentCandidateOffset : PAWN_CANDIDATE_MOVE_COORDINATE)
    {
        candidateDestinationCoordinate = int(this->m_piecePosition) + currentCandidateOffset * getDirection();

        if (BoardUntils::IsValidTileCandidate(candidateDestinationCoordinate))
        {
            if (currentCandidateOffset == 2*NUM_TILES_PER_COL && this->IsFirstMove())
            {
                unsigned int candidateCoordinate = this->m_piecePosition
                        + static_cast<unsigned int>(NUM_TILES_PER_COL * getDirection());

                if (BoardWnd::GetInstance()->IsTileOccupied(board, candidateCoordinate))
                    continue;
            }

            u32 candidateDestCoord = static_cast<unsigned int>(candidateDestinationCoordinate);
            Piece* destPiece = BoardWnd::GetInstance()->GetPieceOnBoard(board, candidateDestCoord);
            if ( !BoardWnd::GetInstance()->IsTileOccupied(board, candidateDestCoord)
                 && ( currentCandidateOffset  == NUM_TILES_PER_COL                              // MOVE
                 ||   (currentCandidateOffset == 2*NUM_TILES_PER_COL && this->IsFirstMove())) )	// JUMP
            {
                legalMoves.push_back(new Move(board, this, destPiece, candidateDestCoord));
            }
            else if (BoardWnd::GetInstance()->IsTileOccupied(board, candidateDestCoord)
                 && (currentCandidateOffset == NUM_TILES_PER_COL-1 || currentCandidateOffset == NUM_TILES_PER_COL+1)
                 && !BoardUntils::IsSameAlliance(this->GetAlliance(), destPiece->GetAlliance()))
            {
                if (   isFirstColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection())
                    || isEightColumnExclusion(this->m_piecePosition, currentCandidateOffset * getDirection()))
                {
                    continue;
                }
                // Attack move
                legalMoves.push_back(new Move(board, this, destPiece, candidateDestCoord));
            }
        }
    }
	return legalMoves;
}


int Pawn::getDirection() const
{
    if (this->GetAlliance() == Alliance::BLACK)
	{
        return 1;
	}
	// else || Alliance::WHITE ||
    return -1;
}

bool Pawn::isPromote() const
{
    if (this->GetAlliance() == Alliance::BLACK)
    {

    }
    return false;
}
