#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include <vector>
class Board;
class Move;

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
        virtual bool isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board) = 0;
        virtual PieceColour getColour() = 0;

        // TODO: Implement make_copy, copy constructor, move constructor
        virtual std::unique_ptr<Piece> make_copy() const = 0;

        /** valid_direction_moves gives ALL possible moves, valid or invalid, that piece can
          * take, depending on what piece it is. For example, for a bishop, it returns all
          * diagonal moves, a rook, all horizontal and vertical moves.
          */
        virtual std::vector<Move> valid_direction_moves(char file, int rank) const = 0;

        bool inBounds(char file, int rank) const;
};

#endif