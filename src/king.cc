#include "king.h"

King::King(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType King::getType(){
    return Piece::King;
}

Piece::PieceColour King::getColour(){
    return colour;
}

bool King::isMoved(){
    return false;
} 

bool King::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    if(board[endRow][endCol]->getColour() == colour){
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