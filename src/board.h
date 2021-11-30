#ifndef BOARD_H
#define BOARD_H
#include <memory>
class Move;
class Piece;

extern const int NUM_OF_SQUARES_PER_SIDE;

// Types of colours for chessboard. 
// Note the British/Canadian spelling of Color, not American Color
enum PieceColour {White, Black, NoColour};

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
        Board &operator=(const Board &other); // Move assignment operator

        /* ESSENTIAL BOARD FUNCTIONS, SO FAR */

        /* Getters and Setters, sort of */
        Piece *getPieceAt(int col, int row) const;
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

        // winner returns the colour of the winner
        PieceColour winner();

        // TEMPORARY OUTPUT OPERATOR
        friend std::ostream &operator<<(std::ostream& out, const Board &board);
    private:
        PieceColour whose_turn;
        std::unique_ptr<Piece> board[8][8];
};

#endif