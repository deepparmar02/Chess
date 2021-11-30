#include "rook.h"

Rook::Rook(Piece::PieceColour colour): Piece{colour}{}

Piece::PieceType Rook::getType(){
    return PieceType::Rook;
}

Piece::PieceColour Rook::getColour(){
    return colour;
}

bool Rook::isMoved(){
    return false;
} 

bool Rook::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}