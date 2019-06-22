#include "Defines.h"
#include <QMouseEvent>
#include "BoardController.h"
#include "Piece.h"
#include "BoardUntils.h"
#include "Move.h"
#include "MoveMgr.h"
#include "BoardWnd.h"
//#include "HistoryWnd.h"
//#include "DeadPieceWnd.h"
//#include "PromoteWnd.h"

typedef vec2<int32_t> vec2i;

BoardController::BoardController(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_modePlayer = EditModeDef::HUMAN_HUMAN;
}

//void BoardController::mousePressEvent(QMouseEvent */*event*/)
//{
////        vec2i pointer2D(event->x(), event->y());

//}

void BoardController::SetSelecetedPiece(const Piece* piece)
{
    m_piece = piece;
}

void BoardController::MoveSelectedPiece(u32 coordinate)
{
    if(BoardWnd::GetInstance()->IsLocked())
        return;
    const Piece* piece = GetSelecetedPiece();
    Alliance currentMoveMaker = GetMoveMaker();
    if (piece && BoardUntils::IsSameAlliance(piece->GetAlliance(), currentMoveMaker))
    {
        for (Move* move : piece->calculateLegalMove(BoardWnd::GetInstance()->GetCurrentBoard()))
        {
            if (move->GetDestCoordinate() == coordinate)
            {
                if(move->IsLegalMove())
                {
                    MovePiece(move);
                }
                else
                {
                    delete move;
                }
            }
            else
            {
                delete move;
            }
        }
    }
}

Alliance BoardController::GetMoveMaker()
{
    return BoardWnd::GetInstance()->GetCurrentBoard().playerTurn;
}


void BoardController::MovePiece(Move *move)
{
    if(BoardWnd::GetInstance()->IsLocked())
        return;

    QChar type = move->GetTypePieceMove();
    QChar alliance = move->GetAlliancePieceMove();

    ////////////////////////// Set here ////////////////////////
    if(move->IsAttackMove())
    {
        move->SetDescription( type + QString(alliance) + QString(" attack ") + move->GetTypePieceIsAttacked() + QString(" ") +QString::number(move->GetDestCoordinate()) );
//        DeadPieceWnd::GetInstance()->AddDeadPiece(move->GetTypePieceIsAttacked(), move->GetAlliancePieceAttack());
    }
    else
    {
        move->SetDescription( type + QString(alliance) + QString(" move to ") +QString::number(move->GetDestCoordinate()) );
    }

    ////////////////////////////////////////////////////////////////////

    MoveMgr::GetInstance()->Do(move);

//    if(move->IsPromoteMove())
//    {
//        Alliance alliance = move->GetAlliancePieceMove() == 'b' ? Alliance::BLACK : Alliance::WHITE;
//        PromoteWnd::GetInstance()->SetPromoteAlliance(alliance);
//        PromoteWnd::GetInstance()->show();
//    }

}

void BoardController::SetModePlayer(BoardController::EditModeDef modePlayer)
{
    m_modePlayer = modePlayer;
}

BoardController::EditModeDef BoardController::GetModePlayer() const
{
    return m_modePlayer;
}
