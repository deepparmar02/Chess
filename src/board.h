#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include "piece.h"
class Move;
class Piece;

// Types of colours for chessboard. 
// Note the British/Canadian spelling of Color, not American Color
// enum PieceColour {White, Black, NoColour};

// TODO: Add initialize function or something

class Board {
    public:
        /**
         * Construct a new Board object.
         * 
         * It sets the board's pieces in their starting, default position.
         * (for now, at least)
         */
        Board();

        /* BIG 5 - We will deep copy the pieces */
        ~Board(); // (deep)-Destroys the Board object
        Board(const Board &other); // Copy constructor
        Board &operator=(const Board &other); // Copy assignment operator
        Board(Board &&other); // Move constructor
        Board &operator=(Board &&other); // Move assignment operator

        /* Getters and Setters, sort of */
        Piece *getPieceAt(char file, int rank) const;
        // cleaner client alternative to getPieceAt
        Piece *operator() (char file, int rank) const;
        void setPieceAt(char file, int rank, Piece &piece);

        /**
         * move takes in the start and end squares, returns if it is
         * valid move (true) or invalid (false) as a boolean, and if true
         * make the move on the board
         */
        // bool move(Move &given_move);
        bool move(char start_file, int start_rank, char end_file, int end_rank);

        /**
         * allPossibleMoves returns an array of valid moves
         * 
         * for now, we store a vector of ints, as dummy type.
         * We'll decide which class or type to use later.
         * 
         * @return std::vector<int> 
         */
        std::vector<int> allPossibleMoves();

        /* GAME STATE METHODS */
        // inCheck checks if current player is in check or not
        bool inCheck();

        // inCheckmate checks if current player is checkmated,
        // ie, king is in check and there are no possible moves to get out
        bool inCheckmate();

        // inStalemate checks if game is in stalemate,
        // ie, king isn't in check but can't make any valid moves
        bool inStalemate();

        // resetBoard goes back to default setup
        void resetBoard();

        // winner returns the colour of the winner
        Piece::PieceColour winner();

        // TEMPORARY OUTPUT OPERATOR
        friend std::ostream &operator<<(std::ostream& out, const Board &board);

        Piece::PieceColour whose_turn; // for now, I'll make it public
    private:
        std::unique_ptr<Piece> board[8][8];

        void defaultSetup();

        // FUTURE FIELDS THAT MIGHT COME USEFUL
        // std::pair<char, int> white_king;
        // std::pair<char, int> black_king;
        // bool white_castle_kingside;
        // bool white_castle_queenside;
        // bool black_castle_kingside;
        // bool black_castle_queenside;
        // Keep track of en passant.
        // std::pair<int, int>en_passant_square;
};

#endif