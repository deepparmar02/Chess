#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: public Piece {
    public:
        explicit Knight(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif