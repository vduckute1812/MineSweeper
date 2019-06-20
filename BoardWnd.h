#ifndef BOARDWND_H
#define BOARDWND_H
#include "Singleton.h"
#include <QWidget>
#include "Piece.h"

#define WAIT_CURSOR \
QApplication::setOverrideCursor(Qt::WaitCursor)

#define NORMAL_CURSOR \
QApplication::restoreOverrideCursor()

#define HIDE_CURSOR \
QApplication::setOverrideCursor(Qt::BlankCursor)


#define SYNC \
while (MainWnd::GetInstance()->IsLocked()) \
Sleep(5)


typedef std::vector<const Piece*> PiecePositions;

struct BoardConfig
{
    PiecePositions  pieceData;
    Alliance        playerTurn;
};

typedef std::vector<Piece*> PieceCollection;

class Tile;
typedef std::vector<Tile*> BoardTiles;

class Piece;
class BoardController;
class BoardWnd: public QWidget, public Singleton<BoardWnd>
{
     Q_OBJECT
public:
    BoardWnd(BoardController* controller = nullptr, QWidget* parent = nullptr);
    ~BoardWnd() override;

    virtual void            Init() override;

    void                    CreateStandardBoard();

public slots:
    // This method forces update of all dependent windows
    void                    Update();

private:
    volatile bool			m_isLocked;
    BoardTiles              m_tiles;

    BoardController*        m_boardController;
    QTimer*                 m_timer;

    BoardConfig             m_currentBoard;

    PieceCollection         m_pieces;
};

#endif // BOARDWND_H
