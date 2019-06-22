#include <QTimer>
#include <QGridLayout>
#include "BoardWnd.h"
#include "Defines.h"
#include "Tile.h"
#include "PieceFactory.h"
#include "BoardUntils.h"

BoardWnd::BoardWnd(BoardController *controller, QWidget *parent/* = nullptr*/):
    QWidget (parent),
    m_boardController(controller)
{
    m_timer = new QTimer(this);

//    // update thread
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()), Qt::QueuedConnection);
//    m_timer->start(50);

    // main thread
    startTimer(20);
}

BoardWnd::~BoardWnd()
{

}

void BoardWnd::Init()
{
    // Create empty tiles and board
    Piece* NULL_PIECE = nullptr;

    for (unsigned int i = 0; i < NUM_TILES; ++i)
    {
        Tile* tile = new Tile(i, NULL_PIECE);
        tile->SetCanTouch(true);    //can touch for making event

        m_tiles.push_back(tile);
        m_currentBoard.pieceData.push_back(NULL_PIECE);
    }

    setMinimumSize(TILE_ROW_SIZE * NUM_TILES_PER_ROW,
                    TILE_COL_SIZE * NUM_TILES_PER_ROW);

    QGridLayout *gridLayout = new QGridLayout();
    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->setParent(this);
        gridLayout->addWidget(tile, tile->GetCoordinate() / NUM_TILES_PER_ROW, tile->GetCoordinate() % NUM_TILES_PER_ROW);
    }

    CreateStandardBoard();

    gridLayout->setSpacing(0);
    setLayout(gridLayout);
}

void BoardWnd::CreateStandardBoard()
{
    Lock(true);
    blockSignals(true);

    ReleaseCollectPiece();
    ResetTiles();

    u32 endBoardIdx = NUM_TILES_PER_ROW * NUM_TILES_PER_COL - 1;
    const QList<QString> listInit = {"Rook","Knight","Bishop","King","Queen","Bishop","Knight","Rook"
                                    ,"Pawn", "Pawn" ,"Pawn"  ,"Pawn","Pawn" , "Pawn" ,"Pawn"  ,"Pawn"};

    u32 sizeInit = static_cast<u32>(listInit.size());
    for(u32 i = 0; i < sizeInit; ++i)
    {
        Piece* piece_white = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::BLACK);
        if(piece_white) //temporary
        piece_white->SetPosition(i);
        m_currentBoard.pieceData.at(i) = piece_white;
        m_pieces.push_back(piece_white);

        Piece* piece_black = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::WHITE);
        if(piece_black) //temporary
        piece_black->SetPosition(endBoardIdx - i);
        m_currentBoard.pieceData.at(endBoardIdx - i) = piece_black;
        m_pieces.push_back(piece_black);
    }

    // Set piece on board
    PiecePositions::iterator piecePtr;
    for (piecePtr = m_currentBoard.pieceData.begin(); piecePtr != m_currentBoard.pieceData.end(); ++piecePtr)
    {
        Piece* piece = (*piecePtr);
        if(piece != nullptr)
        {
            u32 location = piece->GetPosition();
            Tile* tile = m_tiles.at(location);
            tile->SetPiece(piece);
            piece->setParent(tile);
        }
    }
    m_currentBoard.playerTurn = Alliance::WHITE;

    Lock(false);
    blockSignals(false);
}

void BoardWnd::ReleaseCollectPiece()
{
    PieceCollection::iterator piecePtr = m_pieces.begin();

    for (piecePtr = m_pieces.begin(); piecePtr != m_pieces.end(); ++piecePtr)
    {
        delete *piecePtr;
    }
    m_pieces.clear();
}

void BoardWnd::SetBoard(BoardConfig board)
{

}

void BoardWnd::ResetTiles()
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->SetPiece(nullptr);
    }
}

void BoardWnd::SetPieceOnBoard(BoardConfig board, u32 piecePosition, Piece* piece)
{
    board.pieceData.at(piecePosition) = piece;
}

Piece* BoardWnd::GetPieceOnBoard(BoardConfig board, u32 piecePosition) const
{
    return board.pieceData.at(piecePosition);
}

void BoardWnd::SetPieceOnBoard(u32 boardIdx, u32 piecePosition, Piece* piece)
{
    // temporary current board
    m_currentBoard.pieceData.at(piecePosition) = piece;
}

Piece* BoardWnd::GetPieceOnBoard(u32 boardIdx, u32 piecePosition) const
{
    // temporary current board
    return m_currentBoard.pieceData.at(piecePosition);
}

bool BoardWnd::IsTileOccupied(BoardConfig board, u32 tilePosition) const
{
    return board.pieceData.at(tilePosition) != nullptr;
}

u32 BoardWnd::GetKingPosition(BoardConfig board, Alliance player) const
{
    u32 kingPosition = BoardUntils::getMaxTiles();
    PiecePositions::iterator piecePtr = board.pieceData.begin();
    for (;piecePtr!=board.pieceData.end();++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(piece!=nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
        {
            if(piece->GetPieceType() == PieceType::KING)
            {
                kingPosition = piece->GetPosition();
                break;
            }
        }
    }

    return kingPosition;
}

MoveCollection BoardWnd::GetMoveCollections(BoardConfig board, Alliance player)
{
    MoveCollection moveCollection;
    PiecePositions::iterator piecePtr = board.pieceData.begin();
    for (; piecePtr != board.pieceData.end(); ++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(piece != nullptr && BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
        {
            for (Move* move: piece->calculateLegalMove(board))
            {
                moveCollection.push_back(move);
            }
        }
    }
    return moveCollection;
}

void BoardWnd::ResetColorTiles()
{
    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->SetCurrentColor(tile->GetDefaultColor());
    }
}

Tile* BoardWnd::GetTile(u32 coordinate)
{
    return m_tiles.at(coordinate);
}

bool BoardWnd::IsTileOccupied(u32 boardIdx, u32 tilePosition) const
{
    // temporary current board
    return m_currentBoard.pieceData.at(tilePosition) != nullptr;
}

void BoardWnd::Update()
{

}


void BoardWnd::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    repaint();
}

