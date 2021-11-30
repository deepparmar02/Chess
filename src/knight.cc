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
    return true;
}