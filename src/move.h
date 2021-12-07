#ifndef MOVE_H
#define MOVE_H

class Move {
    public:
        char start_file;
        int start_rank;
        char end_file;
        int end_rank;
        char promote_to;

        // Construct a new Move object with default move (no pawn promotion)
        Move(char start_file, int start_rank, char end_file, int end_rank);

        // Overloaded constructor for pawn promotion moves
        Move(char start_file, int start_rank, char end_file, int end_rank, char promote_to);

        ~Move();
};

#endif