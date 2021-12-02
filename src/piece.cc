#include "piece.h"

Piece::Piece(Piece::PieceColour colourPiece) : colour{colourPiece} {}

Piece::~Piece(){}

bool Piece::isEnpassant() {
    return false;
}