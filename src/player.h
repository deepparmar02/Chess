#ifndef PLAYER_H
#define PLAYER_H

class Move;
class Board;

class Player {
    protected: 
        Board &board;
    public:
        explicit Player(Board &board);
        virtual Move make_move() = 0;
        virtual ~Player();
};

#endif