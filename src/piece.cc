#include "piece.h"

Piece::Piece(Piece::PieceColour colourPiece) : colour{colourPiece} {}

Piece::~Piece(){}

Piece::Piece(const Piece &other) : colour{other.colour} {}

bool Piece::isEnpassant() {
    return false;
}