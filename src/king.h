#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
    public:
        King(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif