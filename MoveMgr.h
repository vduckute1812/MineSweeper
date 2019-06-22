#ifndef MOVEMGR_H
#define MOVEMGR_H

#include <vector>
#include "Singleton.h"

class Move;

typedef std::vector<Move*> MoveCollection;

class MoveMgr
{

public:
    MoveMgr();
    ~MoveMgr();

    void                Do(Move* move);

    bool                HasUndo();
    void                Undo();

    bool                HasRedo();
    void                Redo();

    unsigned int        GetIndex() const;
    static MoveMgr*     GetInstance();
    static void         FreeInstance();

    int                 GetCount() const;

    Move*               GetMove(int idx) const;


private:
    static MoveMgr*     s_instance;

    unsigned int        m_moveIdx;
    MoveCollection      m_trackMoves;
};

#endif // MOVEMGR_H
