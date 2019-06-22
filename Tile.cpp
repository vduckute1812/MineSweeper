#include "Tile.h"
#include "Defines.h"
#include "BoardWnd.h"
#include "BoardUntils.h"
#include "BoardController.h"
#include <QPainter>
#include "Move.h"

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
    if(m_piece != nullptr)
    {
        m_piece->ShowPieceImg(this);
    }
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
    if(BoardWnd::GetInstance()->IsLocked() || !m_canTouch)
        return;

//    BoardWnd::GetInstance()->GetEditModeController()->mousePressEvent(event);

    // Make move Piece
    u32 coordinate = this->GetCoordinate();
    BoardController::GetInstance()->MoveSelectedPiece(coordinate);

    BoardController::GetInstance()->SetSelecetedPiece(this->GetPiece());

    // Set colors on Board. Render posible move
    BoardWnd::GetInstance()->ResetColorTiles();
    const Piece* pieceColor = BoardController::GetInstance()->GetSelecetedPiece();

    if (pieceColor  && BoardUntils::IsSameAlliance(pieceColor->GetAlliance(), BoardController::GetInstance()->GetMoveMaker()))
    {
        this->SetCurrentColor(CHOOSE_COLOR);
        for (Move* move : pieceColor->calculateLegalMove(BoardWnd::GetInstance()->GetCurrentBoard()))
        {
            unsigned int destCoordinate = move->GetDestCoordinate();
            Tile* tile = BoardWnd::GetInstance()->GetTile(destCoordinate);
            if(move->IsLegalMove())
            {
                if(move->IsAttackMove())
                {
                    tile->SetCurrentColor(ATTACK_COLOR);
                }
                else
                {
                    tile->SetCurrentColor(MOVE_COLOR);
                }
            }
            delete move;
        }
    }
}

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(m_currentColor);
    painter.drawRect(rect());
}

