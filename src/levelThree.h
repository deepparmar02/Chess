#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include "player.h"

class Move;
class Board;

class LevelThree : public Player {
    public:
        explicit LevelThree(Board &board);

        // If there is no possible move left,
        // it throws a NoMove exception.
        Move make_move() override;        
};

#endif