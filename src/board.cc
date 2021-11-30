#include "board.h"

// NB: Right now, I only added interface. There is no implementation yet.

const int NUM_OF_SQUARES_PER_SIDE = 8;

int charRankToInt(char c) {
    if ('a' <= c && c <= 'h') {
        return c - 'a';
    } else {
        throw;
    }
}

Board::Board();

Board::~Board(); // (deep)-Destroys the Board object
Board::Board(const Board &other); // Copy constructor
Board & Board::operator=(const Board &other); // Copy assignment operator
Board::Board(Board &&other); // Move constructor
Board & Board::operator=(const Board &other); // Move assignment operator

Piece Board::getPieceAt(char col, int row) const;
Piece Board::getPieceAt(int col, int row) const;
void Board::setPieceAt(Piece &piece, char col, int row);
void Board::setPieceAt(Piece &piece, int col, int row);
// cleaner alternative to getPieceAt
// Piece Board::operator() (char col, int row) const;

/* MOVE FUNCTION */
bool Board::move(Move &given_move);
bool Board::move(char startFile, int startRank, char endFile, int endFile);
bool Board::move(char startFile, int startRank, char endFile, int endFile, Piece &promote_to);

/* GAME STATE METHODS */
bool Board::inCheck();
bool Board::inCheckmate();
bool Board::inStalemate();

void Board::resetBoard();