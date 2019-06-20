#ifndef TILE_H
#define TILE_H

#include <QWidget>

typedef unsigned int u32;

static const QBrush ODD_COLOR   ("white");
static const QBrush EVEN_COLOR  ("brown");
static const QBrush MOVE_COLOR	("gray");
static const QBrush ATTACK_COLOR(QColor(255, 100, 0 , 200));    // orangle
static const QBrush CHOOSE_COLOR("yellow");


class Piece;
class Tile: public QWidget
{
public:
    explicit Tile(u32 coordinate, const Piece* piece, QWidget* parent = nullptr);

    void                SetPiece(const Piece* piece);
    const Piece*        GetPiece() const;

    u32                 GetCoordinate() const;
    bool                HasPieceOnTile();

    void                SetCurrentColor(QBrush color);
    QBrush              GetDefaultColor() const;

    void                SetCanTouch(bool yes);
    bool                CanTouch() const;

    // Event system
    void                mousePressEvent(QMouseEvent *) override;
    void                paintEvent(QPaintEvent *) override;

protected:
    // Tile color
    QBrush              m_defaultColor;
    QBrush              m_currentColor;

    const Piece*        m_piece;
    u32                 m_tileCoordinate;

    bool                m_canTouch;
};

#endif // TILE_H
