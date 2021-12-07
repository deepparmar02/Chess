#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include "piece.h"
#include "subject.h"
class Move;
class Piece;

// Types of colours for chessboard. 
// Note the British/Canadian spelling of Color, not American Color
// enum PieceColour {White, Black, NoColour};

class Board : public Subject {
    public:
        // Construct a new Board object. It creates an empty board.
        Board();

        /* BIG 5 - We will deep copy the pieces */
        ~Board(); // (deep)-Destroys the Board object
        Board(const Board &other); // Copy constructor
        Board &operator=(const Board &other); // Copy assignment operator
        Board(Board &&other); // Move constructor
        Board &operator=(Board &&other); // Move assignment operator

        // defaultSetup creates the standard chess setup.
        void defaultSetup();

        /* Getters and Setters, sort of */
        Piece *getPieceAt(char file, int rank) const;
        // cleaner client alternative to getPieceAt
        Piece *operator() (char file, int rank) const;
        void setPieceAt(char file, int rank, std::unique_ptr<Piece> piece);

        /**
         * move takes in the start and end squares, returns if it is
         * valid move (true) or invalid (false) as a boolean, and if true
         * make the move on the board
         */
        // bool move(Move &given_move);
        bool move(char start_file, int start_rank, char end_file, int end_rank);
        bool move(char start_file, int start_rank, char end_file, int end_rank, Piece *promote_to);

        /* GAME STATE METHODS */
        // TODO: Add allPossibleMoves()
        std::vector<Move> allPossibleMoves();
        std::vector<Move> allCapturingMoves();

        // possibleMoveExists checks if current player can make any move or not.
        bool possibleMoveExists();

        // inCheck checks if current player is in check or not
        bool inCheck();

        // inCheckmate checks if current player is checkmated,
        // ie, king is in check and there are no possible moves to get out
        bool inCheckmate();

        // inStalemate checks if game is in stalemate,
        // ie, king isn't in check but can't make any valid moves
        bool inStalemate();

        // isGameOver checks if player is in checkmate or stalemate
        // which means game cannot be continued
        void isGameOver();

        // isTwoKings checks if there are exactly 1 white king 
        // and 1 black king
        bool isTwoKings(); 

        // isPawnLastRow checks if there are no pawns in the last rows
        bool isPawnLastRow();

        // enterSetupMode indicates that player entered setup mode
        void enterSetupMode();

        // endSetupMode checks if setup mode could be exited
        // conditions: 2 kings (1 White, 1 Black), no pawns on last row, no king is in check
        bool endSetupMode();

        // enteredSetupMode checks if player entered setup mode
        bool isCustomBoard();

        // setGameRunning sets isInGame to true
        void setGameRunning();

        // isGameRunning returns whether game is running
        bool isGameRunning();

        // addPiece adds the piece at (file, rank)
        void addPiece(char file, int rank, char piece);

        // deletePiece deletes piece at (file, rank)
        void deletePiece(char file, int rank);

        // changeColour makes it 'colour's' turn to go next
        void changeColour(std::string colour);

        // resetBoard goes back to default setup
        void resetBoard();

        // resign concedes the game to the opponent
        void resign();

        // winner returns the colour of the winner
        // Piece::PieceColour winner();

        // TEMPORARY OUTPUT OPERATOR
        friend std::ostream &operator<<(std::ostream& out, const Board &board);

        // Scores of player 1 and player 2
        int score1;
        int score2;

        Piece::PieceColour whose_turn; // for now, I'll make it public
    private:
        std::unique_ptr<Piece> board[8][8];
        bool isCheckmate;
        bool isStalemate;

        bool enteredSetupMode;
        bool isInGame;

        // FUTURE FIELDS THAT MIGHT COME USEFUL
        // std::pair<char, int> white_king;
        // std::pair<char, int> black_king;
        bool white_castle_kingside;
        bool white_castle_queenside;
        bool black_castle_kingside;
        bool black_castle_queenside;
        // Keep track of en passant.
        char en_passant_file;
        int en_passant_rank;

        std::unique_ptr<Piece> & getPointerAt(char file, int rank);
        void resetEnPassant();
        void setCastlingState(char file, int rank, Piece::PieceType type, bool &castling_status);
        void checkCastling();
        bool move_check(char start_file, int start_rank, char end_file, int end_rank, bool modify_board);
        bool valid_move(char start_file, int start_rank, char end_file, int end_rank, 
                        Piece *promote_to, bool modify_board);
        bool valid_move(char start_file, int start_rank, char end_file, int end_rank, bool modify_board);
        void after_move_housekeeping();

        // for now, we use friend. breaks encapsulation but easy to write and test
        friend class Pawn;
        friend class King;
};

#endif