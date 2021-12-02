#ifndef PIECE_H
#define PIECE_H
#include <memory>
class Board;

class Piece{
    public:
        // Piece Colours
        enum PieceColour {White, Black, NoColour};

        // Piece Type
        enum PieceType {Queen, Rook, King, Knight, Bishop, Pawn, Empty};
        
        PieceColour colour;
        explicit Piece(PieceColour colourPiece);
        Piece(const Piece &other);
        virtual ~Piece();

        virtual PieceType getType() = 0;
        virtual bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board) = 0;
        virtual PieceColour getColour() = 0;
        virtual bool isMoved() = 0; 

        // TODO: Implement make_copy, copy constructor, move constructor
        virtual std::unique_ptr<Piece> make_copy() const = 0;
        virtual bool isEnpassant();
};

#endif