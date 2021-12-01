#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop: public Piece {
    public:
        Bishop(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif