#include "bishop.h"

Bishop::Bishop(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType Bishop::getType(){
    return PieceType::Bishop;
}

Piece::PieceColour Bishop::getColour(){
    return colour;
}

bool Bishop::isMoved(){
    return false;
} 

bool Bishop::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}