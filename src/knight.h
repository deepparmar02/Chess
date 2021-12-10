#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: public Piece {
    public:
        explicit Knight(PieceColour colour);
        Knight(const Knight &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
        std::vector<Move> valid_direction_moves(char file, int rank) const override;
};

#endif