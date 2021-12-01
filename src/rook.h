#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class Rook: public Piece {
    public:
        Rook(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif