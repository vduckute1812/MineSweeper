#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <QWidget>
#include "Singleton.h"
#include "Piece.h"

class BoardController: public Singleton<BoardController>, public QWidget
{
public:
    enum EditModeDef
    {
        HUMAN_HUMAN,
        HUMAN_AI,
        NONE
    };

    BoardController(QWidget* parent = nullptr);
//    void        mousePressEvent(QMouseEvent *) override;

    void        SetSelecetedPiece(const Piece* piece);
    const Piece*      GetSelecetedPiece() const {return m_piece;}

    void        MoveSelectedPiece(unsigned int coordinate);

    Alliance    GetMoveMaker();

    void        MovePiece(Move* move);

    void        SetModePlayer(EditModeDef modePlayer);
    EditModeDef GetModePlayer() const;

private:
    const Piece*          m_piece;
    int             m_coordinate;
    Alliance        m_moveMaker;
    EditModeDef     m_modePlayer;       // Black player is AI default mode
};

#endif // BOARDCONTROLLER_H
