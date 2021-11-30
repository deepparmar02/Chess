#include "pawn.h"

Pawn::Pawn(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType Pawn::getType(){
    return PieceType::Pawn;
}

Piece::PieceColour Pawn::getColour(){
    return colour;
}

bool Pawn::isMoved(){
    return false;
} 

bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}