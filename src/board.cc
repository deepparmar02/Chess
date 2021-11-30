#include "board.h"
#include "piece.h"

// NB: Right now, I only added interface. There is no implementation yet.

const int NUM_OF_SQUARES_PER_SIDE = 8;

Board::Board() : whose_turn{White} {
    
}

Board::~Board() {

}

Board::Board(const Board &other) {

}

Board & Board::operator=(const Board &other) {

}

Board::Board(Board &&other) {

}

Board & Board::operator=(const Board &other) {

}

Piece *Board::getPieceAt(int col, int row) const {

}

void Board::setPieceAt(Piece &piece, int col, int row) {

}
// cleaner alternative to getPieceAt
/*
Piece Board::operator() (char col, int row) const {

} */

/* MOVE FUNCTION */
bool Board::move(Move &given_move) {

}

/* GAME STATE METHODS */
bool Board::inCheck() {

}

bool Board::inCheckmate() {

}

bool Board::inStalemate() {

}

PieceColour Board::winner() {

}

void Board::resetBoard() {

}

std::ostream &operator<<(std::ostream& out, const Board &board) {
    for (int j = 0; j < NUM_OF_SQUARES_PER_SIDE; ++j) {
        out << "-";
    }

    // start with bottom right square being the white square
    for (int i = NUM_OF_SQUARES_PER_SIDE; i >= 0; i--) {
        out << "|";
        for (int j = NUM_OF_SQUARES_PER_SIDE; j >= 0; j--) {
            // if even square, then it is white square
            if (j % 2 == 0) {
                out << "_";
            } else {
                out << " ";
            }
        }
        out << "|";
    }

    for (int j = 0; j < NUM_OF_SQUARES_PER_SIDE; ++j) out << "-";

    return out;
}