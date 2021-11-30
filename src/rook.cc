#include "rook.h"

Rook::Rook(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType Rook::getType(){
    return PieceType::Rook;
}

Piece::PieceColour Rook::getColour(){
    return colour;
}

bool Rook::isMoved(){
    return false;
} 

bool Rook::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    if(board[endRow][endCol]->getColour() == colour){
        return false;
    }
    if(startRow == endRow){ // Checks if there is a piece between startCol and endCol (horizontally)
        int moveDir = (endCol - startCol > 0) ? 1 : -1; // 1 is right 
        for(int i = startCol + moveDir; i != endCol; i += moveDir){
            if(board[startRow][i]->getType() != Empty){
                return false;
            }
        }
        return true;
    }else if(startCol == endCol){ // Checks if there is a piece between startRow and endRow (vertically)
        int moveDir = (endRow - startRow > 0) ? 1 : -1; // 1 is right 
        for(int i = startRow + moveDir; i != endRow; i += moveDir){
            if(board[i][startCol]->getType() != Empty){
                return false;
            }
        }
        return true;
    }
    return false;
}