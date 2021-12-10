#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop: public Piece {
    public:
        explicit Bishop(PieceColour colour);
        Bishop(const Bishop &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
        std::vector<Move> valid_direction_moves(char file, int rank) const override;
};

#endif