#include "board.h"
#include "piece.h"
#include "empty.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "move.h"
#include <iostream>
#include <utility>
using namespace std;

const int NUM_OF_SQUARES_PER_SIDE = 8;

// TEMPORARY CONSTANTS
auto const White = Piece::PieceColour::White;
auto const Black = Piece::PieceColour::Black;

auto const typeEmpty = Piece::PieceType::Empty;
auto const typePawn = Piece::PieceType::Pawn;
auto const typeKnight = Piece::PieceType::Knight;
auto const typeBishop = Piece::PieceType::Bishop;
auto const typeRook = Piece::PieceType::Rook;
auto const typeQueen = Piece::PieceType::Queen;
auto const typeKing = Piece::PieceType::King;


int fileToRow(char c) {
    if ('a' <= c && c <= 'h') {
        return c - 'a';
    } else {
        throw std::out_of_range{"Invalid file."};
    }
}

int rankToCol(int i) {
    if (1 <= i && i <= 8) {
        return i - 1;
    } else {
        throw std::out_of_range{"Invalid rank."};
    }
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

std::unique_ptr<Piece> convertToPiece(char piece){
    if(piece == 'K'){
        return std::make_unique<King>(Piece::PieceColour::White);
    }else if(piece == 'P'){
        return std::make_unique<Pawn>(Piece::PieceColour::White);
    }else if(piece == 'Q'){
        return std::make_unique<Queen>(Piece::PieceColour::White);
    }else if(piece == 'R'){
        return std::make_unique<Rook>(Piece::PieceColour::White);
    }else if(piece == 'N'){
        return std::make_unique<Knight>(Piece::PieceColour::White);
    }else if(piece == 'B'){
        return std::make_unique<Bishop>(Piece::PieceColour::White);
    }else if(piece == 'k'){
        return std::make_unique<King>(Piece::PieceColour::Black);
    }else if(piece == 'p'){
        return std::make_unique<Pawn>(Piece::PieceColour::Black);
    }else if(piece == 'q'){
        return std::make_unique<Queen>(Piece::PieceColour::Black);
    }else if(piece == 'r'){
        return std::make_unique<Rook>(Piece::PieceColour::Black);
    }else if(piece == 'n'){
        return std::make_unique<Knight>(Piece::PieceColour::Black);
    }else if(piece == 'b'){
        return std::make_unique<Bishop>(Piece::PieceColour::Black);
    }
    return std::make_unique<Empty>();
}

// cleaner alternative to getPieceAt
Piece *Board::operator() (char col, int row) const {
    return getPieceAt(col, row);
}

// TODO: Add the castling fields to ctors and assignment methods

// The internal board setup is that white pieces are on the left, black on the right.
// a1 is [0][0], etc. up tp h8 which is [7][7]
Board::Board() : 
    score1{0},
    score2{0},
    whose_turn{Piece::PieceColour::White},
    isCheckmate{false},
    isStalemate{false},
    enteredSetupMode{false},
    isInGame{false},
    white_castle_kingside{false},
    white_castle_queenside{false},
    black_castle_kingside{false},
    black_castle_queenside{false},
    en_passant_file{'\0'},
    en_passant_rank{0},
    allPossibleMoves{std::vector<Move>{}},
    capturingMoves{std::vector<Move>{}}
{
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = std::make_unique<Empty>();
        }
    }
}

void Board::defaultSetup() {
    //default state values
    score1 = 0;
    score2 = 0;
    whose_turn = Piece::PieceColour::White;
    en_passant_file = '\0';
    en_passant_rank = 0;
    isCheckmate = false;
    isStalemate = false;
    white_castle_kingside = true;
    white_castle_queenside = true;
    black_castle_kingside = true;
    black_castle_queenside = true;

    // pawn setup
    for (char c = 'a'; c <= 'h'; ++c) {
        getPointerAt(c, 2) = std::make_unique<Pawn>(Piece::PieceColour::White);
        getPointerAt(c, 7) = std::make_unique<Pawn>(Piece::PieceColour::Black);
    }

    // empty setup
    for (char d = 'a'; d <= 'h'; ++d) {
        for (char r = 3; r <= 6; ++r) {
            getPointerAt(d, r) = std::make_unique<Empty>();
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
        getPointerAt('a', i) = std::make_unique<Rook>(colour);
        getPointerAt('b', i) = std::make_unique<Knight>(colour);
        getPointerAt('c', i) = std::make_unique<Bishop>(colour);
        getPointerAt('d', i) = std::make_unique<Queen>(colour);
        getPointerAt('e', i) = std::make_unique<King>(colour);
        getPointerAt('f', i) = std::make_unique<Bishop>(colour);
        getPointerAt('g', i) = std::make_unique<Knight>(colour);
        getPointerAt('h', i) = std::make_unique<Rook>(colour);
    }
    isGameOver();
}

Board::~Board() { /* NOTHING! Unique pointers do it for me. */ }

Board::Board(const Board &other) : 
    score1{other.score1},
    score2{other.score2},
    whose_turn{other.whose_turn},
    isCheckmate{other.isCheckmate},
    isStalemate{other.isStalemate},
    white_castle_kingside{other.white_castle_kingside},
    white_castle_queenside{other.white_castle_queenside},
    black_castle_kingside{other.black_castle_kingside},
    black_castle_queenside{other.black_castle_queenside},
    en_passant_file{other.en_passant_file},
    en_passant_rank{other.en_passant_rank},
    allPossibleMoves{other.allPossibleMoves},
    capturingMoves{other.capturingMoves}
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
        white_castle_kingside = other.white_castle_kingside;
        white_castle_queenside = other.white_castle_queenside;
        black_castle_kingside = other.black_castle_kingside;
        black_castle_queenside = other.black_castle_queenside;
        en_passant_file = other.en_passant_file;
        en_passant_rank = other.en_passant_rank;
        allPossibleMoves = other.allPossibleMoves;
        capturingMoves = other.capturingMoves;
        for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
            for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
                std::unique_ptr<Piece> newPiece = other.board[r][c]->make_copy();
                std::swap(board[r][c], newPiece);
            }
        }
    }
    return *this;
}

// I'm just experimenting with the default move ctor and operator= 
// just to see if it works or not. Don't delete the commented code for now.

Board::Board(Board &&other) : 
    score1{std::move(other.score1)},
    score2{std::move(other.score2)},
    whose_turn{std::move(other.whose_turn)},
    isCheckmate{std::move(other.isCheckmate)},
    isStalemate{std::move(other.isStalemate)},
    white_castle_kingside{std::move(other.white_castle_kingside)},
    white_castle_queenside{std::move(other.white_castle_queenside)},
    black_castle_kingside{std::move(other.black_castle_kingside)},
    black_castle_queenside{std::move(other.black_castle_queenside)},
    en_passant_file{std::move(other.en_passant_file)},
    en_passant_rank{std::move(other.en_passant_rank)},
    allPossibleMoves{std::move(other.allPossibleMoves)},
    capturingMoves{std::move(other.capturingMoves)}
{
    for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
        for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
            board[r][c] = std::move(other.board[r][c]);
        }
    }
}

Board & Board::operator=(Board &&other) {
    if (this != &other) {
        std::swap(score1, other.score1);
        std::swap(score2, other.score2);
        std::swap(whose_turn, other.whose_turn);
        std::swap(isCheckmate, other.isCheckmate);
        std::swap(isStalemate, other.isStalemate);
        std::swap(white_castle_kingside, other.white_castle_kingside);
        std::swap(white_castle_queenside, other.white_castle_queenside);
        std::swap(black_castle_kingside, other.black_castle_kingside);
        std::swap(black_castle_queenside, other.black_castle_queenside);
        std::swap(en_passant_rank, other.en_passant_rank);
        std::swap(en_passant_file, other.en_passant_file);
        std::swap(allPossibleMoves, other.allPossibleMoves);
        std::swap(capturingMoves, other.capturingMoves);
        for (int r = 0; r < NUM_OF_SQUARES_PER_SIDE; ++r) {
            for (int c = 0; c < NUM_OF_SQUARES_PER_SIDE; ++c) {
                std::swap(other.board[r][c], board[r][c]);
            }
        }
    }
    return *this;
}

void Board::setPieceAt(char file, int rank, std::unique_ptr<Piece> piece) {
    auto newPiece = piece->make_copy();
    std::swap(newPiece, getPointerAt(file, rank));
}

bool Board::inCheck() {
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
                    break;
                }
            }
        }
    }

    return !isPieceSafe(king_file, king_rank);

    // we loop through every square to see if there's a piece that is in sight of
    // capturing the king.
    // for (char f = 'a'; f <= 'h'; ++f) {
    //     for (int r = 1; r <= 8; ++r) {
    //         // if a piece can move and capture the king
    //         if (getPieceAt(f, r)->isValidMove(r, f, king_rank, king_file, *this)) {
    //             return true;
    //         }
    //     }
    // }
    // return false;
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

/**
 * @brief after_move_houseekeeping resets en passant when required, 
 * checks conditions for castling, and checks for checkmate and stalemate
 */
void Board::after_move_housekeeping() {
    int rank_by_colour;
    if (whose_turn == White) {
        // black's en passant square from last turn
        // is in rank 6, so reset when it's black's turn
        whose_turn = Black;
        rank_by_colour = 6;
    } else {
        // white's en passant square from last turn 
        // is in rank 3, so reset when it's white's turn
        whose_turn = White;
        rank_by_colour = 3;
    }

    // reason why we have this if statement is because
    // if white just made 2-square pawn move, then en_passant_rank == 3;
    // if black just made 2-square pawn move, then en_passant_rank == 6;
    // when we switch turns to black, we don't just reset every time we move
    // we only reset when opponent turn passes, hence this if statement.
    if (en_passant_rank == rank_by_colour) {
        resetEnPassant();
    }
    checkCastling();
    isGameOver(); // when this is called, it calls possibleMoveExists.
}

/**
 * @brief move_check only checks if moving from start square to end square
 * will you get yourself in check or not, regardless of how invalid the move is.
 * 
 * It does not attempt to touch other pieces other than when capturing pieces.
 * 
 * If modify_board is false, it retains the state of the board.
 * 
 * If player_in_check != whose_turn, you must retain the state of the board, just
 * so you don't accidentally move yourself in check.
 */
bool Board::move_check(char start_file, int start_rank, char end_file, int end_rank, bool modify_board, Piece::PieceColour player_in_check) {
    std::unique_ptr<Piece> & start_piece = getPointerAt(start_file, start_rank);
    std::unique_ptr<Piece> & end_piece = getPointerAt(end_file, end_rank);

    std::unique_ptr<Piece> capturedPiece = std::make_unique<Empty>();
    std::swap(start_piece, end_piece);
    std::swap(start_piece, capturedPiece);

    std::swap(whose_turn, player_in_check);

    bool in_check = inCheck();
    
    if (in_check || !modify_board || player_in_check != whose_turn) {
        std::swap(start_piece, capturedPiece);
        std::swap(start_piece, end_piece);
    }

    std::swap(whose_turn, player_in_check);

    return in_check;
}

bool Board::move_safe(char start_file, int start_rank, char end_file, int end_rank) {
    std::unique_ptr<Piece> & start_piece = getPointerAt(start_file, start_rank);
    std::unique_ptr<Piece> & end_piece = getPointerAt(end_file, end_rank);

    std::unique_ptr<Piece> capturedPiece = std::make_unique<Empty>();
    std::swap(start_piece, end_piece);
    std::swap(start_piece, capturedPiece);

    bool is_piece_safe = isPieceSafe(end_file, end_rank);
    
    std::swap(start_piece, capturedPiece);
    std::swap(start_piece, end_piece);

    return is_piece_safe;
}

// If modify_board is false, it retains the state of the board.
bool Board::valid_move(char start_file, int start_rank, char end_file, int end_rank, 
                       Piece *promote_to, bool modify_board) {
    std::unique_ptr<Piece> & start_piece = getPointerAt(start_file, start_rank);

    // if you're not touching your own piece.
    if (start_piece->getColour() != whose_turn) {
        return false;
    }

    // if the move is valid according to piece rules, you check if you're not getting yourself into check.
    if (start_piece->isValidMove(start_rank, start_file, end_rank, end_file, *this)) { 
        
        // castling stuff
        bool castling = false;
        char mid_file = (end_file + start_file) / 2;
        int castleRank = 0;
        char rook_start;
        char rook_end;
        if (start_piece->getType() == typeKing && 2 == abs(end_file - start_file)) {
            bool kingside = false;
            bool queenside = false;

            if (whose_turn == White) {
                castleRank = 1;
                kingside = white_castle_kingside;
                queenside = white_castle_queenside;
            } else {
                castleRank = 8;
                kingside = black_castle_kingside;
                queenside = black_castle_queenside;
            }

            if (2 == end_file - start_file && kingside) {
                // kingside castle (note start_rank == end_rank) 
                rook_start = 'h';
                rook_end = 'f';
            } else if (-2 == end_file - start_file && queenside) {
                // queenside castle
                rook_start = 'a';
                rook_end = 'd';
            } else {
                return false;
            }

            // king must not be in check and moving to first intermediate square 
            // also does not get you in check.
            // If that is satisfied, we will move the king down 
            // at line 430 for real (if modify_board is true). 
            // Else, we don't move and it's false.
            castling = !inCheck() && !move_check(start_file, start_rank, mid_file, end_rank, false, whose_turn);
            if (!castling) {
                return false;
            }
        }

        // two-square pawn move stuff
        bool pawnTwoSqaures = false;
        char future_en_passant_file;
        int future_en_passant_rank;

        // en passant stuff    
        bool enPassant = false;
        std::unique_ptr<Piece> enPassantTemp = std::make_unique<Empty>();

        // pawn promotion stuff
        bool pawnPromote = false;
        std::unique_ptr<Piece> promotedPiece = promote_to->make_copy();

        if (start_piece->getType() == typePawn) {
            // set en passant-able square
            if (end_rank - start_rank == 2 && end_file == start_file) {
                future_en_passant_file = start_file;
                future_en_passant_rank = (start_rank + end_rank) / 2;
                pawnTwoSqaures = true;
            }

            // en passant. we swap first because if we don't
            // what happens if that pawn is blocking check.
            if (end_rank == en_passant_rank && end_file == en_passant_file) {
                std::swap(enPassantTemp, getPointerAt(end_file, start_rank));
                enPassant = true;
            }

            // pawn promotion
            if (end_rank == 8) {
                if (promotedPiece->getType() == typeEmpty || promotedPiece->getType() == typePawn) {
                    return false;
                }
                pawnPromote = true;
            }
        }

        // regardless of en passant or pawn promotion or castling, from line 473 - 488
        // this is the default way to check if your move is valid or not.
        bool no_check = !move_check(start_file, start_rank, end_file, end_rank, modify_board, whose_turn);
        // NOTE: IF MOVE IS UNSUCESSFUL, YOU LEAVE ALL BOARD STATES AS IS.
        // YOU DO NOT CHANGE THEM.

        if (no_check && modify_board) {
            // ONLY MAKE CHANGES TO THE BOARD HERE.
            // you promote to a new piece
            if (pawnPromote) {
                getPointerAt(end_file, end_rank) = std::move(promotedPiece);
            }
            // you move the rook to finish castling
            if (castling) {
                std::swap(getPointerAt(rook_start, castleRank), getPointerAt(rook_end, castleRank));
            }
            // if two-square pawn move is sucessful, you set future enpassant square
            if (pawnTwoSqaures) {
                en_passant_file = future_en_passant_file;
                en_passant_rank = future_en_passant_rank;
            }
            after_move_housekeeping();
        } else {
            // if you don't change the board or move is invalid, you put the en passant'ed pawn back
            if (enPassant) {
                std::swap(enPassantTemp, getPointerAt(end_file, start_rank));
            }
            // if two-square pawn move is unsucessful, you do not 
            // reset. you leave it as is, because you might
            // want to take that square again.
        }

        return no_check;

    } else {
        return false;
    }
}

bool Board::move(char start_file, int start_rank, char end_file, int end_rank, Piece *promote_to) {
    return valid_move(start_file, start_rank, end_file, end_rank, promote_to, true);
}

// If modify_board is false, it retains the state of the board.
bool Board::valid_move(char start_file, int start_rank, char end_file, int end_rank, bool modify_board) {
    Empty empty_square{};
    return valid_move(start_file, start_rank, end_file, end_rank, &empty_square, modify_board);
}

bool Board::move(char start_file, int start_rank, char end_file, int end_rank) {
    return valid_move(start_file, start_rank, end_file, end_rank, true);
}

// TODO: Reimplement the overloaded move functions with respect to pawn promotion.
bool Board::move(Move &given_move) {
    char start_file = given_move.start_file;
    int start_rank = given_move.start_rank;
    char end_file = given_move.end_file;
    int end_rank = given_move.end_rank;
    char promote_to = given_move.promote_to;
    if (promote_to == ' ') {
        return move(start_file, start_rank, end_file, end_rank);
    } 
    return move(start_file, start_rank, end_file, end_rank, convertToPiece(promote_to).get());
}


bool Board::possibleMoveExists() {
    allPossibleMoves.clear();
    capturingMoves.clear();
    checkMoves.clear();
    avoidCapturingMoves.clear();

    for (char i = 'a'; i <= 'h'; i++) {
        for (int j = 1; j <= 8; j++){
            auto piece = getPieceAt(i, j);
            std::vector<Move> directional_moves = piece->valid_direction_moves(i, j);
            for (auto move : directional_moves) {
                if (valid_move(move.start_file, move.start_rank, move.end_file, move.end_rank, false)) {
                    // TODO: Does not check if pawn promotion is legal or not, so work on it.

                    Piece::PieceColour opponent = whose_turn == White ? Black : White;
                    
                    allPossibleMoves.push_back(move);
                    if (getPieceAt(move.end_file, move.end_rank)->getType() != typeEmpty) {
                        capturingMoves.push_back(move);
                    }  
                    if (move_check(move.start_file, move.start_rank, move.end_file, move.end_rank, false, opponent)) {
                        checkMoves.push_back(move);
                    }  

                    if (!isPieceSafe(i, j)) {
                        if (move_safe(move.start_file, move.start_rank, move.end_file, move.end_rank)) {
                            avoidCapturingMoves.push_back(move);
                        }
                    }
                }
                
            }
            // if(piece->getType() != Piece::PieceType::Empty){
            //     if(piece->getColour() == whose_turn){
            //         for(char k = 'a'; k <= 'h'; k++){
            //             for(int l = 1; l <= 8; l++){
            //                 if (valid_move(i, j, k, l, false)) {
                                               
            //                 }
            //             }
            //         }
            //     }
            // }
        }
    }
    return !allPossibleMoves.empty();
}

bool Board::isPieceSafe(char file, int rank) {
    // we loop through every square to see if there's a piece that is in sight of
    // capturing the king.
    for (char f = 'a'; f <= 'h'; ++f) {
        for (int r = 1; r <= 8; ++r) {
            // if a piece can move and capture the piece
            if (getPieceAt(f, r)->isValidMove(r, f, rank, file, *this)) {
                return false;
            }
        }
    }
    return true;
}

bool Board::inCheckmate() {
    return isCheckmate;
}

bool Board::inStalemate() {
    return isStalemate;
}

std::vector<Move> Board::getAllPossibleMoves() {
    return allPossibleMoves;
}

std::vector<Move> Board::getAllCapturingMoves() {
    return capturingMoves;
}

std::vector<Move> Board::getCheckMoves() {
    return checkMoves;
}

std::vector<Move> Board::getAvoidCapturingMoves() {
    return avoidCapturingMoves;
}

void Board::isGameOver() {
    bool hasValidMoves = possibleMoveExists(); // this creates a field of all possible moves.
    if (!hasValidMoves) {
        if (inCheck()) {
            isCheckmate = true;
        } else {
            isStalemate = true;
        }
        if(whose_turn == Piece::PieceColour::White){
            score2++;
        }else{
            score1++;
        }
        enteredSetupMode = false;
        isInGame = false;
    }
}

void Board::resign(){
    if(whose_turn == Piece::PieceColour::White){
        score2++;
    }else{
        score1++;
    }
    isInGame = false;
    enteredSetupMode = false;
}

bool Board::isTwoKings() {
    int whiteKings = 0;
    int blackKings = 0;
    for(char i = 'a'; i <= 'h'; i++){
        for(int j = 1; j <= 8; j++){
            if(getPieceAt(i, j)->getType() == Piece::PieceType::King){
                if(getPieceAt(i, j)->getColour() == Piece::PieceColour::White){
                    whiteKings++;
                }else{
                    blackKings++;
                }
                if(whiteKings > 1 || blackKings > 1){
                    return false;
                }
            }
        }
    }
    if(whiteKings != 1 && blackKings != 1){
        return false;
    }
    return true;
}

void Board::changeColour(string colour){
    if(colour == "white"){
        whose_turn = Piece::PieceColour::White;
    }else{
        whose_turn = Piece::PieceColour::Black;
    }
}

void Board::addPiece(char file, int rank, char piece){
    setPieceAt(file, rank, convertToPiece(piece));
}

void Board::deletePiece(char file, int rank) {
    setPieceAt(file, rank, std::make_unique<Empty>());
}

bool Board::isPawnLastRow() {
    for (int i = 1; i <=  8; i++) {
        if (getPieceAt('a', i)->getType() == Piece::PieceType::Pawn ||
            getPieceAt('h', i)->getType() == Piece::PieceType::Pawn) {
            return true;;
        }
    }
    return false;
}

void Board::enterSetupMode() {
    enteredSetupMode = true;
}

bool Board::isGameRunning(){
    return isInGame;
}

void Board::setGameRunning(){
    isInGame = true;
}

bool Board::endSetupMode() {
    if (!isPawnLastRow() && isTwoKings() && !inCheck()) {
        isGameOver();
        return true;
    }
    return false;
}

bool Board::isCustomBoard() {
    return enteredSetupMode;
}

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

// char initializeBoardPiece(Piece::PieceType pieceType, Piece::PieceColour colour) {
//     char piece;
//     if (pieceType == Piece::King) {
//         piece = 'K';
//     } else if (pieceType == Piece::Queen) {
//         piece = 'Q';
//     } else if (pieceType == Piece::Rook) {
//         piece = 'R';
//     } else if (pieceType == Piece::Bishop) {
//         piece = 'B';
//     } else if (pieceType == Piece::Knight) {
//         piece = 'N';
//     } else {
//         piece = 'P';
//     }

//     // if Black piece, then change to lower case
//     if (colour == Piece::Black) {
//         piece = tolower(piece);
//     }
//     return piece;
// }

std::ostream &operator<<(std::ostream& out, const Board & board) {
    // start with top right square being the Piece::PieceColour::white square

    // for (int i = 8; i >= 1; i--) {
    //     int startWithWhite = 0;
    //     if (i % 2 != 0) startWithWhite = 1; 
        
    //     out << i << " ";
    //     for (int j = 0; j < NUM_OF_SQUARES_PER_SIDE; j++) {
    //         Piece * piece = board.getPieceAt(j + 'a', i);
    //         if (piece->getType() != Piece::Empty) {
    //             out << initializeBoardPiece(piece->getType(), piece->getColour());
    //         } else {
    //             if (j % 2 == startWithWhite) {
    //                 out << "_";
    //             } else {
    //                 out << " ";
    //             }
    //         }
    //     }
    //     out << endl;
    // }

    // out << endl;
    // out << "  abcdefgh" << endl;

    return out;
}

