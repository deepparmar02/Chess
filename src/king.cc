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
    return true;
}