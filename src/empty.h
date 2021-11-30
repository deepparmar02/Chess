#ifndef __EMPTY_H__
#define __EMPTY_H__
#include "piece.h"

class Empty: public Piece {
    public:
        Empty();
        PieceType getType() override;
        bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif