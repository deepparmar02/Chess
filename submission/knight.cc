#include "knight.h"
#include "board.h"
#include "move.h"
#include <vector>

Knight::Knight(Piece::PieceColour colour): Piece{colour}{}

Knight::Knight(const Knight &other) : Piece{other.colour} {}

Piece::PieceType Knight::getType(){        return PieceType::Knight;
}

Piece::PieceColour Knight::getColour(){
    return colour;
}

bool Knight::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
        return false;
    }
    if(endCol == startCol + 1 || endCol == startCol - 1){
        if(endRow == startRow + 2 || endRow == startRow - 2){
            if(board.getPieceAt(endCol, endRow)->getColour() != colour){
                return true;
            }
            return false;
        }
    }else if(endCol == startCol + 2 || endCol == startCol - 2){
        if(endRow == startRow + 1 || endRow == startRow - 1){
            if(board.getPieceAt(endCol, endRow)->getColour() != colour){
                return true;
            }
            return false;
        }
    }
    return false;
}

std::unique_ptr<Piece> Knight::make_copy() const {
    auto newPtr = std::make_unique<Knight>(*this);
    return newPtr;
}

std::vector<Move> Knight::valid_direction_moves(char file, int rank) const{
    std::vector<Move> directional_moves;


    if (inBounds(file + 2, rank + 1)) {
        directional_moves.emplace_back(file, rank, file+2, rank+1);
    }

    if (inBounds(file+2, rank-1)){
        directional_moves.emplace_back(file, rank, file+2, rank-1);
    }

    if (inBounds(file - 2, rank + 1)) {
        directional_moves.emplace_back(file, rank, file-2, rank+1);
    }

    if (inBounds(file - 2, rank - 1)) {
        directional_moves.emplace_back(file, rank, file-2, rank-1);
    }

    if (inBounds(file + 1, rank + 2)) {
        directional_moves.emplace_back(file, rank, file+1, rank+2);
    }

    if (inBounds(file + 1, rank - 2)) {
        directional_moves.emplace_back(file, rank, file+1, rank-2);
    }
    
    if (inBounds(file - 1, rank + 2)) {
        directional_moves.emplace_back(file, rank, file-1, rank+2);
    }
    
    if (inBounds(file-1, rank-2)) {
        directional_moves.emplace_back(file, rank, file-1, rank-2);
    }

    return directional_moves;
}