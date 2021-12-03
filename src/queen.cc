#include "queen.h"
#include "board.h"

Queen::Queen(PieceColour colour): Piece{colour}{}

Queen::Queen(const Queen &other) : Piece{other.colour} {}

Piece::PieceType Queen::getType() {
    return PieceType::Queen;
}

Piece::PieceColour Queen::getColour(){
    return colour;
}

bool Queen::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    if(board.getPieceAt(endCol,endRow)->getColour() == colour){
        return false;
    }
    if(startRow == endRow){ // Checks if there is a piece between startCol and endCol (horizontally)
        int moveDir = (endCol - startCol > 0) ? 1 : -1; // 1 is right 
        for(int i = startCol + moveDir; i != endCol; i += moveDir){
            if(board.getPieceAt(i, startRow)->getType() != Empty){
                return false;
            }
        }
        return true;
    }else if(startCol == endCol){ // Checks if there is a piece between startRow and endRow (vertically)
        int moveDir = (endRow - startRow > 0) ? 1 : -1; // 1 is right 
        for(int i = startRow + moveDir; i != endRow; i += moveDir){
            if(board.getPieceAt(startCol, i)->getType() != Empty){
                return false;
            }
        }
        return true;
    }else if(endCol - startCol == endRow - startRow || endCol - startCol == startRow - endRow){ // Checks if there is a piece between startRow, startCol and endRow, endCol (diagonally)
        int rowDir = (endRow - startRow > 0) ? 1 : -1;
        int colDir = (endCol - startCol > 0) ? 1 : -1;
        int j = startCol + colDir;
        for(int i = startRow + rowDir; i != endRow; i += rowDir){
            if(board.getPieceAt(j, i)->getType() != Empty){
                return false;
            }
            j += colDir;
        }
        return true;
    }
    return false;
}

std::unique_ptr<Piece> Queen::make_copy() const {
    auto newPtr = std::make_unique<Queen>(*this);
    return newPtr;
}