#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
class Move;
class Board;

class Human : public Player {
    public:
        explicit Human(Board &board);

        // If it doesn't read enough argments from stdin, 
        // to make a valid-ish Move object, it throws a 
        // NoMove exception.
        virtual Move make_move() override;
};

#endif