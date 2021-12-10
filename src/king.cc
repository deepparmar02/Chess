#include "king.h"
#include "board.h"
#include "move.h"
#include <vector>

King::King(Piece::PieceColour colour): Piece{colour}{}

King::King(const King &other) : Piece{other.colour} {}

Piece::PieceType King::getType() {
    return Piece::King;
}

Piece::PieceColour King::getColour(){
    return colour;
}

bool King::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
        return false;
    }
    int changeRow = endRow - startRow;
    int changeCol = endCol - startCol;
    
    // king should not stay put
    if (changeRow == 0 && changeCol == 0) {
        return false;
    }

    // king can only travel to adjacent squares
    if ((-1 <= changeRow && changeRow <= 1) && (-1 <= changeCol && changeCol <= 1)) {
        return true;
    }

    // however, you're at castling mode
    if (((-2 == changeCol) || (2 == changeCol)) && 'e' == startCol && 0 == changeRow) {
        
        int castleRank;
        bool kingside;
        bool queenside;
        if (colour == White) {
            castleRank = 1;
            kingside = board.white_castle_kingside;
            queenside = board.white_castle_queenside;
        } else if (colour == Black) {
            castleRank = 8;
            kingside = board.black_castle_kingside;
            queenside = board.black_castle_queenside;
        }

        // if you're playing white and in rank 1
        if (startRow == castleRank) {
            // castling kingside
            if (2 == changeCol && kingside) {
                bool empty = board('f',castleRank)->getType() == Empty && 
                             board('g',castleRank)->getType() == Empty &&
                             board('h',castleRank)->getType() == Rook &&
                             board('h',castleRank)->getColour() == colour;
                return empty;
            } else if (-2 == changeCol && queenside) {
                bool empty = board('d',castleRank)->getType() == Empty && 
                             board('c',castleRank)->getType() == Empty && 
                             board('b',castleRank)->getType() == Empty;
                             board('a',castleRank)->getType() == Rook &&
                             board('a',castleRank)->getColour() == colour;
                return empty;
            }
        }
    }

    return false;
}

std::unique_ptr<Piece> King::make_copy() const {
    auto newPtr = std::make_unique<King>(*this);
    return newPtr;
}

std::vector<Move> King::valid_direction_moves(char file, int rank) const {
    std::vector<Move> valid_moves;

    if (inBounds(file, rank + 1)) {
        valid_moves.emplace_back(file, rank, file, rank + 1);
    }
    if (inBounds(file, rank - 1)) {
        valid_moves.emplace_back(file, rank, file, rank - 1);
    }

    if (inBounds(file - 1, rank + 1)) {
        valid_moves.emplace_back(file, rank, file - 1, rank + 1);
    }
    if (inBounds(file + 1, rank + 1)) {
        valid_moves.emplace_back(file, rank, file + 1, rank + 1);
    } 
    if (inBounds(file - 1, rank - 1)) {
        valid_moves.emplace_back(file, rank, file - 1, rank - 1);
    }
    if (inBounds(file + 1, rank - 1)) {
        valid_moves.emplace_back(file, rank, file + 1, rank - 1);
    } 

    if (inBounds(file - 1, rank)) {
        valid_moves.emplace_back(file, rank, file - 1, rank);
    }
    if (inBounds(file + 1, rank)) {
        valid_moves.emplace_back(file, rank, file + 1, rank);
    } 

    return valid_moves;
}