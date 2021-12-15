#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Move;
class Board;

// This is the NoMove exception. Thrown when no move is made 
// by the player.
class NoMove {
    public:
        std::string message;
};

class Player {
    protected: 
        Board &board;
    public:
        explicit Player(Board &board);
        virtual Move make_move() = 0;
        virtual ~Player();
};

#endif