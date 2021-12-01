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

bool Empty::isValidMove(int startRow, char startCol, int endRow, char endCol, Board* board){
    return false;
}