#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: public Piece {
    public:
        explicit Knight(PieceColour colour);
        Knight(const Knight &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
        bool isMoved() override;

};

#endif