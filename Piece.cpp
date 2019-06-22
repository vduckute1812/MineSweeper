#include "Tile.h"
#include "Piece.h"
#include "Defines.h"
#include "LoadImageMng.h"

Piece::Piece(PieceType pieceType, Alliance pieceAlliance, u32 position, QWidget *parent):
    QFrame(parent),
    m_piecePosition(position),
    m_pieceAlliance(pieceAlliance),
    m_pieceType(pieceType)
{
    m_isFirstMove = true;
    m_isVisible = true;
    LoadPieceImage(pieceType, pieceAlliance);
}

Piece::~Piece()
{

}

void Piece::SetPosition(u32 position)
{
    m_piecePosition = position;
}

u32 Piece::GetPosition() const
{
    return m_piecePosition;
}

PieceType Piece::GetPieceType() const
{
    return m_pieceType;
}

Alliance Piece::GetAlliance() const
{
    return m_pieceAlliance;
}

PieceValue Piece::GetPieceValue() const
{
    return m_pieceValue;
}

void Piece::ShowPieceImg(Tile* tile) const
{
    m_isVisible? m_pieceImg->show(): m_pieceImg->hide();
    m_pieceImg->setParent(tile);
}

void Piece::SetFirstMove(bool firstMove)
{
    m_isFirstMove = firstMove;
}

bool Piece::IsFirstMove() const
{
    return m_isFirstMove;
}

void Piece::SetVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

bool Piece::GetVisible() const
{
    return  m_isVisible;
}

  // Update image of piece
void Piece::LoadPieceImage(PieceType pieceType, Alliance pieceAlliance)
{
    // Set image
    m_pieceImg = new QLabel(this);

    const QPixmap pixmap = LoadImageMng::GetInstance()->LoadPixmap( QString(pieceType) + pieceAlliance );

    m_pieceImg->setPixmap(pixmap);
    m_pieceImg->resize(QSize(TILE_ROW_SIZE, TILE_COL_SIZE));
    m_pieceImg->setAlignment(Qt::AlignCenter);
    m_pieceImg->setAttribute(Qt::WA_DeleteOnClose);
    m_pieceImg->show();
}

