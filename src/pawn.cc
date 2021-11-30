#include "Pawn.h"

Pawn:Pawn(PieceColour colour): Piece{colour}{}

PieceType Pawn:getType(){
    return Pawn;
}

PieceColour Pawn:getColour(){
    return colour;
}

bool Pawn:isMoved(){
    return false;
} 

bool Pawn:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    return true;
}