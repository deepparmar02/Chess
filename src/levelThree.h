#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include "player.h"

class Move;
class Board;

class LevelThree : public Player {
    public:
        explicit LevelThree(Board &board);
        Move make_move() override;        
};

#endif