#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(PieceColour colour);
        PieceType getType() override;
        isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) override;
        PieceColour getColour() override;
        bool isMoved() override;

}