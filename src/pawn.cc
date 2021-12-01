#include "pawn.h"

Pawn::Pawn(Piece::PieceColour colour): Piece{colour}{
    hasDouble == false;
}

Piece::PieceType Pawn::getType(){
    return PieceType::Pawn;
}

Piece::PieceColour Pawn::getColour(){
    return colour;
}

bool Pawn::isMoved(){
    return hasDouble;
} 

bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece* board[8][8]){
    if(board[endRow][endCol]->getType() == Empty){
        if(endCol == startCol){
            if(colour == White){
                if(endRow == startRow + 1){
                    hasDouble = false;
                    return true;
                }else if(startRow == 1 && (endRow == startRow + 2) && (board[endRow - 1][endCol] == Empty)){
                    hasDouble = true;
                    return true;
                }
            }else if(endRow == startRow - 1){
                hasDouble = false;
                return true;
            }else if(startRow == 6 && (endRow == startRow - 2) && (board[endRow + 1][endCol] == Empty)){
                hasDouble = true;
                return true;
            }
        }else if((endCol == startCol + 1) || (endCol == startCol - 1)){ // en passant
            if(colour == White){
                if(board[startRow][endCol]->getType() == Pawn && board[startRow][endCol]->getColour() != White && board[startRow][endCol]->isMoved() == true){ // adjacent pawn is of different colour has moved double
                    if(endRow = startRow + 1){
                        hasDouble = false;
                        return true;
                    }
                }
            }else{
                if(board[startRow][endCol]->getType() == Pawn && board[startRow][endCol]->getColour() == White && board[startRow][endCol]->isMoved() == true){ // adjacent pawn is of different colour has moved double
                    if(endRow = startRow - 1){
                        hasDouble = false;
                        return true;
                    }
                }
            }
        }
    }else if(board[endRow][endCol]->getColour() != colour){
        if((endCol == startCol + 1) || (endCol == startCol - 1)){
            if(colour == White){
                if(endRow == startRow + 1){
                    hasDouble = false;
                    return true;
                }
            }else if(endRow == startRow - 1){
                hasDouble = false;
                return true;
            }
        }
    }
    return false;
}