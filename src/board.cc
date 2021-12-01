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
using namespace std;

const int NUM_OF_SQUARES_PER_SIDE = 8;

// NB: First index is the row number, second index is the column number
Board::Board() : whose_turn{Piece::PieceColour::White} {
    // Empty squares setup
    for (int row = 2; row <= 5; ++row) {
        for (int col = 0; col < NUM_OF_SQUARES_PER_SIDE; ++col) {
            board[row][col] = std::make_unique<Empty>();
        }
    }

    // Pawn setup
    for (int i = 0; i < NUM_OF_SQUARES_PER_SIDE; ++i) {
        board[1][i] = std::make_unique<Pawn>(Piece::PieceColour::Black);
        board[6][i] = std::make_unique<Pawn>(Piece::PieceColour::White);
    }

    // Remaining piece setup
    for (int j = 0; j <= 7; j += 7) {
        Piece::PieceColour colour;
        if (j == 7) { // j==7 means Piece::PieceColour::white row
            colour = Piece::PieceColour::White;
        } else if (j == 0) { // j==0 means Piece::PieceColour::black row
            colour = Piece::PieceColour::Black;
        }
        // Both Piece::PieceColour::white and Piece::PieceColour::black set up so they mirror each other.
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

Board::~Board() { /* NOTHING! Unique pointers do it for me. */ }

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

Piece *Board::getPieceAt(int row, int col) const {
    return board[row][col].get();
}

void Board::setPieceAt(Piece &piece, int col, int row) {
    auto newPiece = createBasedOnPieceType(piece);
    std::swap(newPiece, board[row][col]);
}
// cleaner alternative to getPieceAt
/*
Piece *Board::operator() (char col, int row) const {
    return getPieceAt(col, row);
} */

/* MOVE FUNCTION */
bool Board::move(int startRow, int startCol, int endRow, int endCol) {
    bool moveable = true/*board[startRow][startCol]->isValidMove(startRow, startCol, endRow, endCol, *this)*/;
    if (moveable) {
        std::swap(board[startRow][startCol], board[endRow][endCol]);
        if (inCheck()) {
            std::swap(board[startRow][startCol], board[endRow][endCol]);
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
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
            Piece* piece = board.getPieceAt(j, i);
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

