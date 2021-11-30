#include "queen.h"

Queen:Queen(PieceColour colour): Piece{colour}{}

PieceType Queen:getType(){
    return // PieceType(QUEEN)
}

bool Queen:isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    if(startRow == endRow){
        int moveDir = (endCol - startCol > 0) ? 1 : -1; // 1 is right 
        for(int i = startCol + moveDir; i != endCol; i += moveDir){
            if()
        }
    }
}