#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"
#include "BoardWnd.h"

class Board;
enum TypeMove
{
    MAJOR_MOVE,
    ATTACK_MOVE,
    PAWN_PROMOTION,
    DEFEND_MOVE,        // NOT YET
    KING_SIDE_CASTLE,   // NOT YET
    QUEEN_SIDE_CASTLE,  // NOT YET
    CHECK_MOVE          // NOT YET
};

class Move
{
public:
    Move(const BoardConfig board, const Piece* movePiece, const Piece* attackPiece, const unsigned int destCoord);

    BoardConfig          Execute();
    BoardConfig          UndoExecute();

    // Use on Board
    BoardConfig          Redo();
    BoardConfig          Undo();

    unsigned int        GetMoveCoordinate() const;
    unsigned int        GetDestCoordinate() const;
    bool                IsAttackMove() const;

    bool                IsLegalMove();
    bool                IsPromoteMove();

    void				SetDescription(const QString& desc);
    const QString&		GetDescription() const;

    QChar               GetTypePieceMove() const;
    QChar               GetTypePieceIsAttacked() const;

    QChar               GetAlliancePieceMove() const;
    QChar               GetAlliancePieceAttack() const;

protected:
    BoardConfig         m_board;
    const Piece*        m_movePiece;
    const Piece*        m_attackPiece;
    Piece*              m_killedPiece;

    bool                m_isFirstMove;
    unsigned int        m_movedCoordinate;
    unsigned int        m_destCoordinate;
    QString             m_description;
};
#endif // MOVE_H
