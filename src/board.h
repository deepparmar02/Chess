#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include "piece.h"
#include "subject.h"
//class Move;
#include "move.h"
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
        // emptyBoard goes back to a clean, empty board
        void emptyBoard();

        /* Getters and Setters, sort of */
        // If 'a' <= file <= 'h' or 1 <= rank <= 8, a std::out_of_range is thrown.
        Piece *getPieceAt(char file, int rank) const;
        // cleaner client alternative to getPieceAt
        Piece *operator() (char file, int rank) const;

        // will not work if isCustomBoard is false.
        void setPieceAt(char file, int rank, std::unique_ptr<Piece> piece);

        /**
         * move takes in the start and end squares, returns if it is
         * valid move (true) or invalid (false) as a boolean, and if true
         * make the move on the board
         * 
         * will not work if isGameRunning is false
         */
        bool move(char start_file, int start_rank, char end_file, int end_rank);
        bool move(char start_file, int start_rank, char end_file, int end_rank, Piece *promote_to);
        bool move(Move &move);

        /* GAME STATE METHODS */
        std::vector<Move> getAllPossibleMoves();
        std::vector<Move> getAllCapturingMoves();
        std::vector<Move> getCheckMoves();
        std::vector<Move> getAvoidCapturingMoves();
        // NOTE: Calling getChangedBoxes returns the array and clears the array contained inside
        std::vector<std::pair<char, int>> getChangedBoxes();

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
        // won't work when not in setup mode
        void addPiece(char file, int rank, char piece);

        // deletePiece deletes piece at (file, rank)
        // won't work when not in setup mode
        void deletePiece(char file, int rank);

        // changeColour makes it 'colour's' turn to go next
        // won't work when not in setup mode
        void changeColour(Piece::PieceColour colour);

        // resign concedes the game to the opponent
        void resign();

        // isPieceSafe checks if the piece at (file, rank) is safe
        bool isPieceSafe(char file, int rank);

        // getScore returns the final scores of white and black
        double getScoreWhite();
        double getScoreBlack();

        // winner returns the colour of the winner
        // Piece::PieceColour winner();

        // TEMPORARY OUTPUT OPERATOR
        friend std::ostream &operator<<(std::ostream& out, const Board &board);

        // current_turn gives the turn of current player
        Piece::PieceColour current_turn();

    private:
        std::unique_ptr<Piece> board[8][8];

        Piece::PieceColour whose_turn;

        bool isCheckmate;
        bool isStalemate;

        // Scores of white and black
        double score_white;
        double score_black;
        
        bool enteredSetupMode;
        bool isInGame;

        // Castling fields
        bool white_castle_kingside;
        bool white_castle_queenside;
        bool black_castle_kingside;
        bool black_castle_queenside;

        // Keep track of en passant.
        char en_passant_file;
        int en_passant_rank;

        std::vector<Move> allPossibleMoves;
        std::vector<Move> capturingMoves;
        std::vector<Move> checkMoves;
        std::vector<Move> avoidCapturingMoves;
        std::vector<std::pair<char, int>> changedBoxes; 

        std::unique_ptr<Piece> & getPointerAt(char file, int rank);
        void resetEnPassant();
        void setCastlingState(char file, int rank, Piece::PieceType type, bool &castling_status);
        void checkCastling();
        bool move_check(char start_file, int start_rank, char end_file, int end_rank, bool modify_board, Piece::PieceColour player_in_check);
        bool valid_move(char start_file, int start_rank, char end_file, int end_rank, 
                        Piece *promote_to, bool modify_board);
        bool valid_move(char start_file, int start_rank, char end_file, int end_rank, bool modify_board);
        void after_move_housekeeping();
        bool move_safe(char start_file, int start_rank, char end_file, int end_rank);
        void emptyBoardChange(bool announce_change);

        // for now, we use friend. breaks encapsulation but easy to write and test
        friend class Pawn;
        friend class King;
};

#endif
