#include "Bishop.h"

Bishop:Bishop(PieceColour colour): Piece{colour}{}

PieceType Bishop:getType(){
    return Bishop;
}

PieceColour Bishop:getColour(){
    return colour;
}

bool Bishop:isMoved(){
    return false;
} 

bool Bishop:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}