#include "piece.h"

Piece::Piece(Piece::PieceColour colourPiece) : colour{colourPiece} {}

Piece::~Piece(){}

Piece::Piece(const Piece &other) : colour{other.colour} {}

// bool Piece::isEnpassant() const {
//     return false;
// }

bool Piece::inBounds(char file, int rank) const {
    if (file >='a' && file <= 'h' && rank >= 1 && rank <= 8) {
        return true;
    }
    return false;
}