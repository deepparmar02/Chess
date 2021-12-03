#include "rook.h"
#include "board.h"

Rook::Rook(Piece::PieceColour colour): Piece{colour}{}

Rook::Rook(const Rook &other) : Piece{other.colour} {}

Piece::PieceType Rook::getType() {
    return PieceType::Rook;
}

Piece::PieceColour Rook::getColour(){
    return colour;
}

bool Rook::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
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
    }
    return false;
}

std::unique_ptr<Piece> Rook::make_copy() const {
    auto newPtr = std::make_unique<Rook>(*this);
    return newPtr;
}