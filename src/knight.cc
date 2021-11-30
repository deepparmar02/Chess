#include "knight.h"

Knight::Knight(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType Knight::getType(){
    return PieceType::Knight;
}

Piece::PieceColour Knight::getColour(){
    return colour;
}

bool Knight::isMoved(){
    return false;
} 

bool Knight::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    if(endCol == endCol + 1 || endCol == endCol - 1){
        if(endRow == startRow + 2 || endRow == startRow - 2){
            if(board[endRow][endCol]->getColour() != colour){
                return true;
            }
            return false;
        }
    }else if(endCol == endCol + 2 || endCol == endCol - 2){
        if(endRow == startRow + 1 || endRow == startRow - 1){
            if(board[endRow][endCol]->getColour() != colour){
                return true;
            }
            return false;
        }
    }
    return false;
}