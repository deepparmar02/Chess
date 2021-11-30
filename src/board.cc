#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

const int NUM_OF_SQUARES_PER_SIDE = 8;

// NB: First index is the row number, second index is the column number
Board::Board() : whose_turn{White} {
    // Empty squares setup
    for (int row = 2; row <= 5; ++row) {
        for (int col = 0; col < NUM_OF_SQUARES_PER_SIDE; ++col) {
            board[row][col] = std::make_unique<Empty>();
        }
    }

    // Pawn setup
    for (int i = 0; i < NUM_OF_SQUARES_PER_SIDE; ++i) {
        board[1][i] = std::make_unique<Pawn>(Black);
        board[6][i] = std::make_unique<Pawn>(White);
    }

    // Remaining piece setup
    for (int j = 0; j <= 7; j += 7) {
        PieceColour colour;
        if (j == 7) { // j==7 means white row
            colour = White;
        } else if (j == 0) { // j==0 means black row
            colour = Black;
        }
        // Both white and black set up so they mirror each other.
        board[j][0] = std::make_unique<Rook>(colour);
        board[j][1] = std::make_unique<Knight>(colour);
        board[j][2] = std::make_unique<Bishop>(colour);
        board[j][3] = std::make_unique<Queen>(colour);
        board[j][4] = std::make_unique<King>(colour);
        board[j][5] = std::make_unique<Bishop>(colour);
        board[j][6] = std::make_unique<Knight>(colour);
        board[j][7] = std::make_unique<Rook>(colour);
    }
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

}