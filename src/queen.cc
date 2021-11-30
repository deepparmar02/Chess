#include "queen.h"

Queen:Queen(PieceColour colour): Piece{colour}{}

PieceType Queen:getType(){
    return Queen;
}

PieceColour Queen:getColour(){
    return colour;
}

bool Queen:isMoved(){
    return false;
} 

bool Queen:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
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
    }else if(endCol - startCol == endRow - startRow || endCol - startCol == startRow - endRow){ // Checks if there is a piece between startRow, startCol and endRow, endCol (diagonally)
        int rowDir = (endRow - startRow > 0) ? 1 : -1;
        int colDir = (endCol - startCol > 0) ? 1 : -1;
        int j = startCol + colDir;
        for(int i = startRow + rowDir; i != endRow; i += rowDir){
            if(board[i][j]->getType != Empty){
                return false;
            }
            j += colDir;
        }
        return true;
    }
    return false;
}