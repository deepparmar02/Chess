#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(PieceColour colour);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board) override;
        PieceColour getColour() override;
        bool isMoved() override; // returns if pawn has moved double or not
        bool isEnpassant() override;
    
    private:
        bool hasDouble;
        bool isEnpassantMove;

};

#endif
