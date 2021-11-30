#ifndef PIECE_H
#define PIECE_H

class Piece{
    public:
        PieceColour color;
        virtual ~Piece();

        virtual PieceType getType() = 0;
        virtual bool isValidMove() = 0;
        virtual PieceColour getColour() = 0;
        virtual bool isMoved() = 0; 
};

#endif