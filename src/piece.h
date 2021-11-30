#ifndef PIECE_H
#define PIECE_H

class Piece{
    public:
        PieceColour colour;
        Piece(PieceColour colourPiece);
        virtual ~Piece();

        virtual PieceType getType() = 0;
        virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]) = 0;
        virtual PieceColour getColour() = 0;
        virtual bool isMoved() = 0; 
};

#endif