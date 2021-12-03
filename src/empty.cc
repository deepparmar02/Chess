#include "empty.h"

Empty::Empty(): Piece{NoColour}{}

Empty::Empty(const Empty &other) : Piece{other.colour} {}

Piece::PieceType Empty::getType() {
    return PieceType::Empty;
}

Piece::PieceColour Empty::getColour(){
    return colour;
}

bool Empty::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    return false;
}

std::unique_ptr<Piece> Empty::make_copy() const {
    auto newPtr = std::make_unique<Empty>(*this);
    return newPtr;
}