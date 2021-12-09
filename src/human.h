#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
class Move;
class Board;

class Human : public Player {
    public:
        explicit Human(Board &board);
        virtual Move make_move() override;
};

#endif