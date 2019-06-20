#include "Tile.h"
#include "Defines.h"
#include <QPainter>

Tile::Tile(u32 coordinate, const Piece *piece, QWidget *parent):
    QWidget (parent),
    m_piece(piece),
    m_tileCoordinate(coordinate)
{
    resize(TILE_ROW_SIZE, TILE_COL_SIZE);

    m_defaultColor = (m_tileCoordinate + (m_tileCoordinate / NUM_TILES_PER_ROW) % 2) % 2 ? ODD_COLOR : EVEN_COLOR;
    m_currentColor = m_defaultColor;
    m_canTouch = false;
}

void Tile::SetPiece(const Piece *piece)
{
    m_piece = piece;
}

const Piece *Tile::GetPiece() const
{
    return m_piece;
}

u32 Tile::GetCoordinate() const
{
    return m_tileCoordinate;
}

bool Tile::HasPieceOnTile()
{
    return m_piece != nullptr;
}

void Tile::SetCurrentColor(QBrush color)
{
    m_currentColor = color;
}

QBrush Tile::GetDefaultColor() const
{
    return m_defaultColor;
}

void Tile::SetCanTouch(bool yes)
{
    m_canTouch = yes;
}

bool Tile::CanTouch() const
{
    return m_canTouch;
}

void Tile::mousePressEvent(QMouseEvent *)
{
    if( !m_canTouch )
    {
        return;
    }
}

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
}

