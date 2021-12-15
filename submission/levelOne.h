#ifndef LEVELONE_H
#define LEVELONE_H
#include "player.h"

class Move;
class Board;

class LevelOne : public Player {
    public:
        explicit LevelOne(Board &board);

        // If there is no possible move left, 
        // it throws a NoMove exception.
        virtual Move make_move() override;        
};

#endif