#include <QTimer>
#include "BoardWnd.h"
#include "Defines.h"
#include "Tile.h"

BoardWnd::BoardWnd(BoardController *controller, QWidget *parent/* = nullptr*/):
    QWidget (parent),
    m_boardController(controller)
{
    m_timer = new QTimer(this);

    // update thread
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()), Qt::QueuedConnection);
    m_timer->start(50);

    // main thread
    startTimer(20);
}

BoardWnd::~BoardWnd()
{

}

void BoardWnd::Init()
{
    // Create empty tiles
    Piece* NULL_PIECE = nullptr;

    for (unsigned int i = 0; i < NUM_TILES; ++i)
    {
        Tile* tile = new Tile(i, NULL_PIECE);
        tile->SetCanTouch(true);
        m_tiles.push_back(tile);
    }



}

void BoardWnd::CreateStandardBoard()
{
    u32 endBoardIdx = NUM_TILES_PER_ROW * NUM_TILES_PER_COL - 1;
    const QList<QString> listInit = {"Rook","Knight","Bishop","King","Queen","Bishop","Knight","Rook"
                                    ,"Pawn", "Pawn" ,"Pawn"  ,"Pawn","Pawn" , "Pawn" ,"Pawn"  ,"Pawn"};

//    u32 sizeInit = static_cast<u32>(listInit.size());
//    for(u32 i = 0; i < sizeInit; ++i)
//    {
//        Piece* piece_white = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::BLACK);
//        piece_white->SetPosition(i);
//        s_tempBoards[0].m_boardValue.at(i).second = piece_white;
//        s_pieces.push_back(piece_white);

//        Piece* piece_black = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::WHITE);
//        piece_black->SetPosition(endBoardIdx - i);
//        s_tempBoards[0].m_boardValue.at(endBoardIdx - i).second = piece_black;
//        s_pieces.push_back(piece_black);
//    }

//    s_tempBoards[0].m_playerTurn = Alliance::WHITE;

//    s_tmpStateIdx++;

//return s_tempBoards[0];
}

void BoardWnd::Update()
{

}
