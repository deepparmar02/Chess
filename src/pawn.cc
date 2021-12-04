#include "pawn.h"
#include "board.h"
#include <iostream>
using namespace std;

Pawn::Pawn(Piece::PieceColour colour): Piece{colour} {}

Pawn::Pawn(const Pawn &other) : 
    Piece{other.colour}
{}

Piece::PieceType Pawn::getType() {
    return PieceType::Pawn;
}

Piece::PieceColour Pawn::getColour(){
    return colour;
}


bool Pawn::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    if (board(endCol,endRow)->getColour() == colour){
        return false;
    }
    int dir, starting_pawn_rank;
    Piece::PieceColour opponent;
    if (colour == White) {
        dir = 1;
        starting_pawn_rank = 2;
        opponent = Black;
    } else {
        dir = -1;
        starting_pawn_rank = 7;
        opponent = White;
    }

    if (startCol == endCol) {
        if (board(startCol, startRow + dir)->getType() != Empty) {
            return false;
        } else if (endRow - startRow == dir) {
            return true;
        } else if (startRow == starting_pawn_rank && endRow - startRow == dir * 2) {
            return board(endCol, endRow)->getType() == Empty;
        } else {
            return false;
        }
    } else if (endCol - startCol == 1 || endCol - startCol == -1) {
        if (endRow - startRow != dir) {
            return false;
        } else if (board(endCol, endRow)->getColour() == opponent) {
            return true;
        } else if (endRow == board.en_passant_rank && endCol == board.en_passant_file) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

std::unique_ptr<Piece> Pawn::make_copy() const {
    auto newPtr = std::make_unique<Pawn>(*this);
    return newPtr;
}