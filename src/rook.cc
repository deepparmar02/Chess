#include "Rook.h"

Rook:Rook(PieceColour colour): Piece{colour}{}

PieceType Rook:getType(){
    return Rook;
}

PieceColour Rook:getColour(){
    return colour;
}

bool Rook:isMoved(){
    return false;
} 

bool Rook:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}