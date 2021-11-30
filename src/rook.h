#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class Rook: public Piece {
    public:
        Rook(PieceColour colour);
        PieceType getType() override;
        isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) override;
        PieceColour getColour() override;
        bool isMoved() override;

}

#endif