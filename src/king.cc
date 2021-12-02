#include "king.h"
#include "board.h"

King::King(Piece::PieceColour colour): Piece{colour}{}

King::King(const King &other) : Piece{other.colour} {}

Piece::PieceType King::getType() {
    return Piece::King;
}

Piece::PieceColour King::getColour(){
    return colour;
}

bool King::isMoved(){
    return false;
} 

bool King::isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
        return false;
    }
    int changeRow = endRow - startRow;
    int changeCol = endCol - startCol;

    if(changeCol == -1 || changeCol == 1){
        if(changeRow == 1 || changeRow == -1){
            return true;
        }else if(changeRow == 0){
            return true;
        }
    }else if(changeCol == 0){
        if(changeRow == 1 || changeRow == -1){
            return true;
        }
    }
    return false;
}

std::unique_ptr<Piece> King::make_copy() const {
    auto newPtr = std::make_unique<King>(*this);
    return newPtr;
}