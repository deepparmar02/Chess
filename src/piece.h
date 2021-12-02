#ifndef PIECE_H
#define PIECE_H

class Board;

class Piece{
    public:
        // Piece Colours
        enum PieceColour {White, Black, NoColour};

        // Piece Type
        enum PieceType {Queen, Rook, King, Knight, Bishop, Pawn, Empty};
        
        PieceColour colour;
        Piece(PieceColour colourPiece);
        virtual ~Piece();

        virtual PieceType getType() = 0;
        virtual bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board) = 0;
        virtual PieceColour getColour() = 0;
        virtual bool isMoved() = 0; 
        virtual bool isEnpassant();
};

#endif