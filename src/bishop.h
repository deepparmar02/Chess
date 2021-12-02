#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop: public Piece {
    public:
        explicit Bishop(PieceColour colour);
        Bishop(const Bishop &other);
        PieceType getType() override;
        bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board) override;
        PieceColour getColour() override;
        std::unique_ptr<Piece> make_copy() const override;
        bool isMoved() override;

};

#endif