#include "empty.h"

Empty::Empty(): Piece{NoColour}{}

Piece::PieceType Empty::getType(){
    return PieceType::Empty;
}

Piece::PieceColour Empty::getColour(){
    return colour;
}

bool Empty::isMoved(){
    return false;
} 

bool Empty::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return false;
}