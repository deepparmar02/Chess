#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class Rook: public Piece {
    public:
        explicit Rook(PieceColour colour);
        Rook(const Rook &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
};

#endif