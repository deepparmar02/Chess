#ifndef BOARD_H
#define BOARD_H
#include <memory>
class Move;
class Piece;

extern const int NUM_OF_SQUARES_PER_SIDE;

// TODO: Add initialize function or something

class Board {
    public:
        // Types of colours for chessboard. 
        // Note the British/Canadian spelling of Color, not American Color
        enum Colour {White, Black, NoColour};

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
        Board &operator=(const Board &other); // Move assignment operator

        /* ESSENTIAL BOARD FUNCTIONS, SO FAR */

        /* Getters and Setters, sort of */
        Piece getPieceAt(char col, int row) const;
        Piece getPieceAt(int col, int row) const;
        void setPieceAt(Piece &piece, char col, int row);
        void setPieceAt(Piece &piece, int col, int row);
        // cleaner alternative to getPieceAt
        // Piece operator() (char col, int row) const;

        /**
         * move takes in the start and end squares, returns if it is
         * valid move (true) or invalid (false) as a boolean, and if true
         * make the move on the board
         * 
         * @return true 
         * @return false 
         */
        bool move(Move &given_move);
        // File = column, Rank = row
        bool move(char startFile, int startRank, char endFile, int endRank);
        bool move(char startFile, int startRank, 
                  char endFile, int endRank, Piece &promote_to);

        /* GAME STATE METHODS */
        // inCheck checks if current player is in check or not
        bool inCheck();

        // inCheckmate checks if current player is checkmated
        bool inCheckmate();

        // inStalemate checks if current player isn't in check 
        // but can't make any valid moves
        bool inStalemate();

        // resetBoard goes back to default setup
        void resetBoard();
    private:
        Colour whose_turn;
        std::unique_ptr<Piece> board[8][8];
};

#endif