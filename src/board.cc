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

std::unique_ptr<Piece> & Board::getPointerAt(char file, int rank) {
    int ridx = fileToRow(file);
    int cidx = rankToCol(rank);
    return board[ridx][cidx];
}

Piece *Board::getPieceAt(char file, int rank) const {
    int ridx = fileToRow(file);
    int cidx = rankToCol(rank);
    return board[ridx][cidx].get();
}

// cleaner alternative to getPieceAt
Piece *Board::operator() (char col, int row) const {
    return getPieceAt(col, row);
}

// The internal board setup is that white pieces are on the left, black on the right.
// a1 is [0][0], etc. up tp h8 which is [7][7]
Board::Board() : 
    whose_turn{Piece::PieceColour::White},
    isCheckmate{false},
    isStalemate{false},
    en_passant_file{'\0'},
    en_passant_rank{'\0'}
{
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = std::make_unique<Empty>();
        }
    }
}

void Board::defaultSetup() {
    //default state values
    whose_turn = Piece::PieceColour::White;
    en_passant_file = '\0';
    en_passant_rank = 0;
    isCheckmate = false;
    isStalemate = false;

    // pawn setup
    for (char c = 'a'; c <= 'h'; ++c) {
        board[fileToRow(c)][rankToCol(2)] = std::make_unique<Pawn>(Piece::PieceColour::White);
        board[fileToRow(c)][rankToCol(7)] = std::make_unique<Pawn>(Piece::PieceColour::Black);
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

Board::Board(const Board &other) : 
    whose_turn{other.whose_turn},
    isCheckmate{other.isCheckmate},
    isStalemate{other.isStalemate},
    en_passant_file{other.en_passant_file},
    en_passant_rank{other.en_passant_rank}
{
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = other.board[r][c]->make_copy();
        }
    }
}

Board & Board::operator=(const Board &other) {
    if (this != &other) {
        whose_turn = other.whose_turn;
        isCheckmate = other.isCheckmate;
        isStalemate = other.isStalemate;
        en_passant_file = other.en_passant_file;
        en_passant_rank = other.en_passant_rank;
        for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
            for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
                std::unique_ptr<Piece> newPiece = other.board[r][c]->make_copy();
                std::swap(board[r][c], newPiece);
            }
        }
    }
    return *this;
}

Board::Board(Board &&other) : 
    whose_turn{std::move(other.whose_turn)},
    isCheckmate{std::move(other.isCheckmate)},
    isStalemate{std::move(other.isStalemate)},
    en_passant_file{std::move(other.en_passant_file)},
    en_passant_rank{std::move(other.en_passant_rank)}
{
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = std::move(other.board[r][c]);
        }
    }
}

Board & Board::operator=(Board &&other) {
    if (this != &other) {
        std::swap(whose_turn, other.whose_turn);
        std::swap(isCheckmate, other.isCheckmate);
        std::swap(isStalemate, other.isStalemate);
        std::swap(en_passant_rank, other.en_passant_rank);
        std::swap(en_passant_file, other.en_passant_file);
        for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
            for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
                std::swap(other.board[r][c], board[r][c]);
            }
        }
    }
    return *this;
}

void Board::setPieceAt(char file, int rank, Piece *piece) {
    auto newPiece = piece->make_copy();
    std::swap(newPiece, board[fileToRow(file)][rankToCol(rank)]);
}

/* GAME STATE METHODS */
bool Board::inCheck() {
    // I can think of two ways to implement this. 

    // This implemenation feels very "code by interface". For every square,
    // I just find if the King can be captured by any piece on the board.
    // If yes, it's check. This can be a bit inefficient, because I check
    // every square, but isValidMove does some polymorphismy-encapsulationy
    // dark magic: it just checks if at that place, it can capture. I don't
    // have to worry about the specific ways a piece can capture the king.
    char king_file;
    int king_rank;

    // here, we find where the king is. Inefficient but certain
    for (char f = 'a'; f <= 'h'; ++f) {
        for (int r = 1; r <= 8; ++r) {
            auto piece = getPieceAt(f, r);
            if (piece->getType() == Piece::PieceType::King) {
                if (piece->getColour() == whose_turn) {
                    king_file = f;
                    king_rank = r;
                }
            }
        }
    }

    // we loop through every square to see if there's a piece that is in sight of
    // capturing the king.
    for (char f = 'a'; f <= 'h'; ++f) {
        for (int r = 1; r <= 8; ++r) {
            // if a piece can move and capture the king
            if (getPieceAt(f, r)->isValidMove(r, f, king_rank, king_file, *this)) {
                return true;
            }
        }
    }
    return false;

    // The second implementation I can think of is more "code by implementation." 
    // From the king's position, I can check for every direction (up-down, left-right, 
    // diagonals, knight-hops) to see if the first non-empty piece I encounter is 
    // an opponent's respective piece or not.
    // For example, if I go horizontal and vertical, I check if there's a rook or queen.
    // If I go diagonal, I check if there's a queen, bishop or pawn.
    // If I go knight-hops, is there a knight.
}

// reset en_passant_every time you start your move
void Board::resetEnPassant() {
    en_passant_file = '\0';
    en_passant_rank = 0;
}

void Board::setCastlingState(char file, int rank, Piece::PieceType type, bool &castling_status) {
    if (getPieceAt(file, rank)->getType() != type) {
        castling_status = false;
    }
}

void Board::checkCastling() {
    // constants for pawn, king and rook, so I don't have to type.
    auto typePawn = Piece::PieceType::Pawn;
    auto typeKing = Piece::PieceType::King;
    auto typeRook = Piece::PieceType::Rook;

    // if white king has moved, even when it moved back, it lost the ability to castle
    setCastlingState('e',1, typeKing, white_castle_kingside);
    setCastlingState('e',1, typeKing, white_castle_queenside);
    
    // if black king has moved, even when it moved back, it lost the ability to castle
    setCastlingState('e',8, typeKing, black_castle_kingside);
    setCastlingState('e',8, typeKing, black_castle_queenside);

    // white queen-side rook
    setCastlingState('a',1, typeRook, white_castle_queenside);
    // white king-side rook
    setCastlingState('h',1, typeRook, white_castle_kingside);
    // black queen-side rook
    setCastlingState('a',8, typeRook, black_castle_queenside);
    // black king-side rook
    setCastlingState('h',8, typeRook, black_castle_kingside);

}

/* MOVE FUNCTION */
bool Board::move(char start_file, int start_rank, char end_file, int end_rank) {
    // constants for pawn, king and rook, so I don't have to type.
    auto typePawn = Piece::PieceType::Pawn;
    auto typeKing = Piece::PieceType::King;
    auto typeRook = Piece::PieceType::Rook;

    // colour constants
    auto White = Piece::PieceColour::White;
    auto Black = Piece::PieceColour::Black;

    std::unique_ptr<Piece> & start_piece = getPointerAt(start_file, start_rank);
    std::unique_ptr<Piece> & end_piece = getPointerAt(end_file, end_rank);

    if (start_piece->getColour() != whose_turn) {
        return false;
    }
    if (start_piece->isValidMove(start_rank, start_file, end_rank, end_file, *this)) {
        std::unique_ptr<Piece> capturedPiece = std::make_unique<Empty>();
        std::swap(start_piece, end_piece);
        std::swap(start_piece, capturedPiece);

        bool castleAttempt = false;
        std::unique_ptr<Piece> rookTemp = std::make_unique<Empty>();
        
        if (end_piece->getType() == typeKing) { // we attempt castling
            
        } 
        
        bool enPassant = false;
        std::unique_ptr<Piece> enPassantTemp = std::make_unique<Empty>();

        if (end_piece->getType() == typePawn) {
            // set en passant square
            if (end_rank - start_rank == 2 && end_file == start_file) {
                en_passant_file = start_file;
                en_passant_rank = (start_rank + end_rank) / 2;
            }

            // en passant
            if (end_rank == en_passant_rank && end_file == en_passant_file) {
                std::swap(enPassantTemp, getPointerAt(end_file, start_rank));
                enPassant = true;
            }

            // pawn promotion
            // if (end_rank == 8) {

            // } else {

            // }
        }

        if (inCheck()) {
            if (enPassant) {
                std::swap(enPassantTemp, getPointerAt(end_file, start_rank));
            }
            std::swap(start_piece, capturedPiece);
            std::swap(start_piece, end_piece);
            resetEnPassant();
            // checkCastling();
            return false;
        } else {
            if (whose_turn == White) {
                whose_turn = Black;
                // black's en passant square from last turn
                // is in rank 6, so reset when it's black's turn
                if (en_passant_rank == 6) {
                    resetEnPassant();
                }
            } else {
                whose_turn = White;
                // white's en passant square from last turn 
                // is in rank 3, so reset when it's white's turn
                if (en_passant_rank == 3) {
                    resetEnPassant();
                }
            }

            checkCastling();
            
            return true;
        }
    } else {
        return false;
    }
}

// we currently store int as a dummy type. We'll decide which class to use later
std::vector<int> Board::allPossibleMoves() {
    std::vector<int> allMoves;
    allMoves.push_back(0); // temporarily fill allMoves with something so it returns false
    return allMoves;
}

bool Board::possibleMoveExists() {
    for (char i = 'a'; i <= 'h'; i++) {
        for (int j = 1; j <= 8; j++){
            auto piece = getPieceAt(i, j);
            if(piece->getType() != Piece::PieceType::Empty){
                if(piece->getColour() == whose_turn){
                    for(char k = 'a'; k <= 'h'; k++){
                        for(int l = 1; l <= 8; l++){
                            if(piece->isValidMove(j, i, l, k, *this)){
                                // Moving to check for check
                                int sridx = fileToRow(i);
                                int scidx = rankToCol(j);
                                int eridx = fileToRow(k);
                                int ecidx = rankToCol(l);

                                std::unique_ptr<Piece> temp = std::make_unique<Empty>();

                                std::swap(board[sridx][scidx], board[eridx][ecidx]);
                                std::swap(temp, board[sridx][scidx]);

                                bool isEnpassantMove = board[eridx][ecidx]->getType() == Piece::PieceType::Pawn && board[eridx][ecidx]->isEnpassant();
                                Piece::PieceColour next_turn =  board[eridx][ecidx]->getColour() == Piece::PieceColour::White ? Piece::PieceColour::Black : Piece::PieceColour::White; 

                                if (isEnpassantMove) {
                                    board[eridx][scidx] = std::make_unique<Empty>(); // setPieceAt coult be used here
                                }
                                bool check = inCheck();
                                
                                // Undoing the moves
                                std::swap(temp, board[sridx][scidx]);
                                std::swap(board[sridx][scidx], board[eridx][ecidx]);
                                if (isEnpassantMove) {
                                    board[sridx][ecidx] = std::make_unique<Pawn>(next_turn);
                                }
                                if(!check){
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}



bool Board::inCheckmate() {
    return isCheckmate;
}

bool Board::inStalemate() {
    return isStalemate;
}

void Board::isGameOver() {
    bool hasValidMoves = possibleMoveExists();
    if (!hasValidMoves) {
        if (inCheck()) {
            isCheckmate = true;
        } else {
            isStalemate = true;
        }
    }
}

// bool Board::move(Move &given_move) {
//     int startRow = given_move.startRow;
//     int startCol = given_move.startCol;
//     int endRow = given_move.endRow;
//     int endCol = given_move.endCol;
//     return move(startRow, startCol, endRow, endCol);
// }

// Piece::PieceColour Board::winner() {
//     return Piece::PieceColour::NoColour;
//     // if (/* */) {
//     //     return Piece::PieceColour::White;
//     // } else {
//     //     return Piece::PieceColour::Black;
//     // }
// }

void Board::resetBoard() {
    defaultSetup();
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
    for (int i = 8; i >= 1; i--) {
        int startWithWhite = 0;
        if (i % 2 != 0) startWithWhite = 1; 
        
        out << i << " ";
        for (int j = 0; j < NUM_OF_SQUARES_PER_SIDE; j++) {
            Piece * piece = board.getPieceAt(j + 'a', i);
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

