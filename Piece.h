#ifndef PIECE_H
#define PIECE_H
#include <QFrame>
#include <QLabel>

class Move;

typedef unsigned int u32;
typedef std::vector<Move*> MoveCollection;

enum Alliance
{
    WHITE = 'w',
    BLACK = 'b'
};

enum PieceType
{
    ROOK	= 'R',
    KNIGHT	= 'K',
    BISHOP	= 'B',
    QUEEN	= 'Q',
    KING	= 'Z',
    PAWN	= 'P'
};

enum PieceValue
{
    PAWN_VALUE =    100,
    KNIGHT_VALUE =  300,
    BISHOP_VALUE =  300,
    ROOK_VALUE =    500,
    QUEEN_VALUE =   900,
    KING_VALUE =    1000
};

class BoardConfig;
class Piece: public QFrame
{
public:
    explicit Piece( PieceType pieceType, Alliance pieceAlliance, u32 position=0, QWidget *parent = nullptr);
    virtual ~Piece();

    virtual MoveCollection  calculateLegalMove(const BoardConfig board) const = 0;
    virtual bool            isFirstColumnExclusion(u32 currentPosition, int candidateOffset) const = 0;
    virtual bool            isEightColumnExclusion(u32 currentPosition, int candidateOffset) const = 0;

    void                    SetPosition(u32 position);
    u32                     GetPosition() const;

    PieceType               GetPieceType() const;
    Alliance                GetAlliance() const;
    PieceValue              GetPieceValue() const;
    QLabel*                 GetRenderImg() const;

    void                    SetFirstMove(bool firstMove);
    bool                    IsFirstMove() const;

    void                    SetVisible(bool isVisible);
    bool                    GetVisible() const;

    void                    LoadPieceImage(PieceType pieceType, Alliance pieceAlliance);

protected:
    u32                     m_piecePosition;
    Alliance                m_pieceAlliance;
    PieceType               m_pieceType;
    PieceValue              m_pieceValue;

    bool                    m_isVisible;        // if false: the piece is dead or unvisible

    bool                    m_isFirstMove;
    QLabel*                 m_pieceImg;
};

#endif // PIECE_H
