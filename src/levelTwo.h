#ifndef LEVELTWO_H
#define LEVELTWO_H
#include "player.h"

class Move;
class Board;

class LevelTwo : public Player {
    public:
        explicit LevelTwo(Board &board);
        Move make_move();        
};

#endif