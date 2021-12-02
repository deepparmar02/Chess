#include "pawn.h"
#include "board.h"

Pawn::Pawn(Piece::PieceColour colour): Piece{colour}{
    hasDouble = false;
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

bool Pawn::isValidMove(int startRow, char startCol, int endRow, char endCol, Board& board){
    if(board.getPieceAt(endCol, endRow)->getType() == Empty){
        if(endCol == startCol){
            if(colour == White){
                if(endRow == startRow + 1){
                    hasDouble = false;
                    return true;
                }else if(startRow == 2 && (endRow == startRow + 2) && (board.getPieceAt(endCol, endRow - 1)->getType() == Empty)){
                    hasDouble = true;
                    return true;
                }
            }else if(endRow == startRow - 1){
                hasDouble = false;
                return true;
            }else if(startRow == 7 && (endRow == startRow - 2) && (board.getPieceAt(endCol, endRow + 1)->getType() == Empty)){
                hasDouble = true;
                return true;
            }
        }else if((endCol == startCol + 1) || (endCol == startCol - 1)){ // en passant
            if(colour == White){
                if(board.getPieceAt(endCol, startRow)->getType() == PieceType::Pawn && board.getPieceAt(endCol, startRow)->getColour() != White && board.getPieceAt(endCol, startRow)->isMoved() == true){ // adjacent pawn is of different colour has moved double
                    if(endRow == startRow + 1){
                        hasDouble = false;
                        return true;
                    }
                }
            }else{
                if(board.getPieceAt(endCol, startRow)->getType() == PieceType::Pawn && board.getPieceAt(endCol, startRow)->getColour() == White && board.getPieceAt(endCol, startRow)->isMoved() == true){ // adjacent pawn is of different colour has moved double
                    if(endRow == startRow - 1){
                        hasDouble = false;
                        return true;
                    }
                }
            }
        }
    }else if(board.getPieceAt(endCol, endRow)->getColour() != colour){
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