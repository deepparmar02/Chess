#include "bishop.h"
#include "board.h"

Bishop::Bishop(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType Bishop::getType() {
    return PieceType::Bishop;
}

Piece::PieceColour Bishop::getColour() {
    return colour;
}

bool Bishop::isMoved() {
    return false;
} 

bool Bishop::isValidMove(int startRow, char startCol, int endRow, char endCol, Board & board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
        return false;
    }
    if(endCol - startCol == endRow - startRow || endCol - startCol == startRow - endRow){ // Checks if there is a piece between startRow, startCol and endRow, endCol (diagonally)
        int rowDir = (endRow - startRow > 0) ? 1 : -1;
        char colDir = (endCol - startCol > 0) ? 1 : -1;
        char j = startCol + colDir;
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