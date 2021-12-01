#include "knight.h"
#include "board.h"
#include <iostream>
using namespace std;

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

bool Knight::isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
        return false;
    }
    if(endCol == startCol + 1 || endCol == startCol - 1){
        if(endRow == startRow + 2 || endRow == startRow - 2){
            if(board.getPieceAt(endCol, endRow)->getColour() != colour){
                return true;
            }
            return false;
        }
    }else if(endCol == startCol + 2 || endCol == startCol - 2){
        if(endRow == startRow + 1 || endRow == startRow - 1){
            if(board.getPieceAt(endCol, endRow)->getColour() != colour){
                return true;
            }
            return false;
        }
    }
    return false;
}