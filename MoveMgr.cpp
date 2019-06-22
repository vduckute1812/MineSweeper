#include "MoveMgr.h"
#include "Move.h"
#include "BoardWnd.h"
//#include "DeadPieceWnd.h"

MoveMgr* MoveMgr::s_instance = nullptr;

//////////////////////////////////////////////////////////////////////////

MoveMgr::MoveMgr()
{
    m_moveIdx = 0;
}

//////////////////////////////////////////////////////////////////////////

MoveMgr::~MoveMgr()
{
    for (unsigned int i = 0; i < m_trackMoves.size(); i++)
        delete m_trackMoves[i];

    m_trackMoves.resize(0);
    m_moveIdx = 0;
}

//////////////////////////////////////////////////////////////////////////

MoveMgr* MoveMgr::GetInstance()
{
    if (!s_instance)
        s_instance = new MoveMgr();

    return s_instance;
}

//////////////////////////////////////////////////////////////////////////


void MoveMgr::FreeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

/////////////////////////////////////////////////////////////////////////

int MoveMgr::GetCount() const
{
    return static_cast<int>(m_trackMoves.size());
}

Move *MoveMgr::GetMove(int idx) const
{
    if (idx < GetCount())
        return m_trackMoves.at(idx);
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////


// Use for generate board after move

void MoveMgr::Do(Move *move)
{
    if(!move || BoardWnd::GetInstance()->IsLocked())
        return;

    BoardWnd::GetInstance()->Lock(true);
    BoardWnd::GetInstance()->blockSignals(true);


    // remove pre-move
    unsigned int currentIndex =  m_moveIdx;
    for (; currentIndex < m_trackMoves.size(); ++currentIndex)
    {
        delete m_trackMoves[currentIndex];
    }

    // after delete pre-move. Set size of available track
    m_trackMoves.resize(m_moveIdx);

    m_moveIdx++;

    BoardConfig board = move->Execute();
    m_trackMoves.push_back(move);

    BoardWnd::GetInstance()->SetBoard(board);

    BoardWnd::GetInstance()->Lock(false);
    BoardWnd::GetInstance()->blockSignals(false);

}


// Undo and redo just use in GUI
bool MoveMgr::HasUndo()
{
    return m_moveIdx > 0;
}

void MoveMgr::Undo()
{
    if(BoardWnd::GetInstance()->IsLocked())
        return;

    BoardWnd::GetInstance()->Lock(true);
    BoardWnd::GetInstance()->blockSignals(true);

    if(HasUndo())
    {
        m_moveIdx--;
        unsigned int currentIdx = static_cast<unsigned int>(m_moveIdx);
        BoardConfig board = m_trackMoves[currentIdx]->Undo();
        BoardWnd::GetInstance()->SetBoard(board);
        Move* move = m_trackMoves.at(m_moveIdx);
//        if(move->IsAttackMove())
//        {
//            DeadPieceWnd::GetInstance()->RemoveDeadPiece(move->GetAlliancePieceAttack());
//        }
    }

    BoardWnd::GetInstance()->Lock(false);
    BoardWnd::GetInstance()->blockSignals(false);
}

bool MoveMgr::HasRedo()
{
    return m_moveIdx < m_trackMoves.size();
}

void MoveMgr::Redo()
{
    if(BoardWnd::GetInstance()->IsLocked())
        return;

    BoardWnd::GetInstance()->Lock(true);
    BoardWnd::GetInstance()->blockSignals(true);

    if(HasRedo())
    {
        unsigned int currentIdx = static_cast<unsigned int>(m_moveIdx);
        Move* move = m_trackMoves.at(m_moveIdx);
//        if(move->IsAttackMove())
//        {
//            DeadPieceWnd::GetInstance()->AddDeadPiece(move->GetTypePieceIsAttacked(), move->GetAlliancePieceAttack());
//        }
        BoardConfig board = m_trackMoves[currentIdx]->Redo();
        BoardWnd::GetInstance()->SetBoard(board);
        m_moveIdx++;
    }

    BoardWnd::GetInstance()->Lock(false);
    BoardWnd::GetInstance()->blockSignals(false);
}


unsigned int MoveMgr::GetIndex() const
{
    return m_moveIdx;
}
