#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: public Piece {
    public:
        Knight(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif