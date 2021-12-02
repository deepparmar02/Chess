#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"

class Queen: public Piece {
    public:
        explicit Queen(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board) override;
        PieceColour getColour() override;
        bool isMoved() override;

};

#endif