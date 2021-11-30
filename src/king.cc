#include "King.h"

King:King(PieceColour colour): Piece{colour}{}

PieceType King:getType(){
    return King;
}

PieceColour King:getColour(){
    return colour;
}

bool King:isMoved(){
    return false;
} 

bool King:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}