#ifndef __EMPTY_H__
#define __EMPTY_H__
#include "piece.h"

class Empty: public Piece {
    public:
        Empty();
        Empty(const Empty &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
        std::vector<Move> valid_direction_moves(char file, int rank) const override;
};

#endif