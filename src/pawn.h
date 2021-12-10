#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
    public:
        explicit Pawn(PieceColour colour);
        Pawn(const Pawn &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
        std::vector<Move> valid_direction_moves(char file, int rank) const override;
};

#endif
