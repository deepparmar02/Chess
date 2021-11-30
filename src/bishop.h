#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Knight: public Piece {
    public:
        Bishop(PieceColour colour);
        PieceType getType() override;
        isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) override;
        PieceColour getColour() override;
        bool isMoved() override;

}