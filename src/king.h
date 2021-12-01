#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
    public:
        King(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif