#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"

class Queen: public Piece {
    public:
        explicit Queen(PieceColour colour);
        Queen(const Queen &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
};

#endif