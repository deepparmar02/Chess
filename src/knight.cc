#include "Knight.h"

Knight:Knight(PieceColour colour): Piece{colour}{}

PieceType Knight:getType(){
    return Knight;
}

PieceColour Knight:getColour(){
    return colour;
}

bool Knight:isMoved(){
    return false;
} 

bool Knight:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}