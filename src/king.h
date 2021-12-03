#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
    public:
        explicit King(PieceColour colour);
        King(const King &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
};

#endif