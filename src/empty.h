#ifndef __EMPTY_H__
#define __EMPTY_H__
#include "piece.h"

class Empty: public Piece {
    public:
        Empty();
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif