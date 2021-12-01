#include "board.h"
#include "piece.h"
#include "empty.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include <iostream>
#include <utility>
using namespace std;

const int NUM_OF_SQUARES_PER_SIDE = 8;

int fileToRow(char c) {
    if ('a' <= c && c <= 'h') {
        return c - 'a';
    } else {
        throw;
    }
}

int rankToCol(int i) {
    if (1 <= i && i <= 8) {
        return i - 1;
    } else {
        throw;
    }
}

std::pair<int, int> getIndexes(char file, int rank) {
    int rowidx = fileToRow(file);
    int colidx = rankToCol(rank);
    return std::make_pair(rowidx, colidx);
}

Piece *Board::getPieceAt(char file, int rank) const {
    int ridx = fileToRow(file);
    int cidx = rankToCol(rank);
    return board[ridx][cidx].get();
}

// The internal board setup is that white pieces are on the left, black on the right.
// a1 is [0][0], etc. up tp h8 which is [7][7]
Board::Board() : whose_turn{Piece::PieceColour::White} {
    // pawn setup
    for (char c = 'a'; c <= 'h'; ++c) {
        board[fileToRow('a')][rankToCol(1)] = std::make_unique<Pawn>(Piece::PieceColour::White);
        board[fileToRow('a')][rankToCol(1)] = std::make_unique<Pawn>(Piece::PieceColour::White);
    }

    // empty setup
    for (char d = 'a'; d <= 'h'; ++d) {
        for (char r = 3; r <= 6; ++r) {
            int ridx = fileToRow(d);
            int cidx = rankToCol(r);
            board[ridx][cidx] = std::make_unique<Empty>();
        }
    }

    // rest of pieces setup
    for (int i = 1; i <= 8; i += 7) {
        Piece::PieceColour colour;
        if (1 == i) {
            colour = Piece::PieceColour::White;
        } else {
            colour = Piece::PieceColour::Black;
        }
        board[fileToRow('a')][rankToCol(i)] = std::make_unique<Rook>(colour);
        board[fileToRow('b')][rankToCol(i)] = std::make_unique<Knight>(colour);
        board[fileToRow('c')][rankToCol(i)] = std::make_unique<Bishop>(colour);
        board[fileToRow('d')][rankToCol(i)] = std::make_unique<Queen>(colour);
        board[fileToRow('e')][rankToCol(i)] = std::make_unique<King>(colour);
        board[fileToRow('f')][rankToCol(i)] = std::make_unique<Bishop>(colour);
        board[fileToRow('g')][rankToCol(i)] = std::make_unique<Knight>(colour);
        board[fileToRow('h')][rankToCol(i)] = std::make_unique<Rook>(colour);
    }
}

Board::~Board() { /* NOTHING! Unique pointers do it for me. */ }

// TODO: Tell Vansh about explicit and make copy constructors
std::unique_ptr<Piece> createBasedOnPieceType(Piece &piece) {
    std::unique_ptr<Piece> newPiece;
    // if (piece.getType() == Piece::PieceType::King) {
    //     newPiece = std::make_unique<King>(piece);
    // } else if (piece.getType() == Piece::PieceType::Queen) {
    //     newPiece = std::make_unique<Queen>(piece);
    // } else if (piece.getType() == Piece::PieceType::Rook) {
    //     newPiece = std::make_unique<Rook>(piece);
    // } else if (piece.getType() == Piece::PieceType::Knight) {
    //     newPiece = std::make_unique<Knight>(piece);
    // } else if (piece.getType() == Piece::PieceType::Pawn) {
    //     newPiece = std::make_unique<Pawn>(piece);
    // } else if (piece.getType() == Piece::PieceType::Empty) {
    //     newPiece = std::make_unique<Empty>(piece);
    // }
    return newPiece;
}

Board::Board(const Board &other) : whose_turn{other.whose_turn} {
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = createBasedOnPieceType(*other.board[r][c]);
        }
    }
}

Board & Board::operator=(const Board &other) {
    if (this != &other) {
        whose_turn = other.whose_turn;
        for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
            for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
                auto newPiece = createBasedOnPieceType(*other.board[r][c]);
                std::swap(board[r][c], newPiece);
            }
        }
    }
    return *this;
}

Board::Board(Board &&other) : whose_turn{std::move(other.whose_turn)} {
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = std::move(other.board[r][c]);
        }
    }
}

Board & Board::operator=(Board &&other) {
    if (this != &other) {
        std::swap(whose_turn, other.whose_turn);
        for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
            for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
                std::swap(other.board[r][c], board[r][c]);
            }
        }
    }
    return *this;
}

void Board::setPieceAt(char file, int rank, Piece &piece) {
    return;
}
// cleaner alternative to getPieceAt
/*
Piece *Board::operator() (char col, int row) const {
    return getPieceAt(col, row);
} */

/* MOVE FUNCTION */
bool Board::move(char start_file, int start_rank, char end_file, int end_rank) {
    /*
    if (isCheckMate()) {
        return false;
    }
    if (getPieceAt(start_file, start_rank)->getColour() == ) */
    return false;
}

// bool Board::move(Move &given_move) {
//     int startRow = given_move.startRow;
//     int startCol = given_move.startCol;
//     int endRow = given_move.endRow;
//     int endCol = given_move.endCol;
//     return move(startRow, startCol, endRow, endCol);
// }

/* GAME STATE METHODS */
bool Board::inCheck() {
    return false;
}

bool Board::inCheckmate() {
    return false;
}

bool Board::inStalemate() {
    return false;
}

Piece::PieceColour Board::winner() {
    return Piece::PieceColour::NoColour;
}

void Board::resetBoard() {
    return;
}

char initializeBoardPiece(Piece::PieceType pieceType, Piece::PieceColour colour) {
    char piece;
    if (pieceType == Piece::King) {
        piece = 'K';
    } else if (pieceType == Piece::Queen) {
        piece = 'Q';
    } else if (pieceType == Piece::Rook) {
        piece = 'R';
    } else if (pieceType == Piece::Bishop) {
        piece = 'B';
    } else if (pieceType == Piece::Knight) {
        piece = 'N';
    } else {
        piece = 'P';
    }

    // if Black piece, then change to lower case
    if (colour == Piece::Black) {
        piece = tolower(piece);
    }
    return piece;
}

std::ostream &operator<<(std::ostream& out, const Board & board) {
    // start with top right square being the Piece::PieceColour::white square
    for (int i = 0; i < NUM_OF_SQUARES_PER_SIDE; i++) {
        int startWithWhite = 0;
        if (i % 2 != 0) startWithWhite = 1; 
        out << NUM_OF_SQUARES_PER_SIDE - i << " ";
        for (int j = 0; j < NUM_OF_SQUARES_PER_SIDE; j++) {
            Piece* piece = board.getPieceAt(i, j); // TODO: Tell Deep I swapped row and column just to match conventions
            if (piece->getType() != Piece::Empty) {
                out << initializeBoardPiece(piece->getType(), piece->getColour());
            } else {
                if (j % 2 == startWithWhite) {
                    out << "_";
                } else {
                    out << " ";
                }
            }
        }
        out << endl;
    }

    out << endl;
    out << "  abcdefgh" << endl;

    return out;
}

