#ifndef LEVELONE_H
#define LEVELONE_H
#include "player.h"

class Move;
class Board;

class LevelOne : public Player {
    public:
        explicit LevelOne(Board &board);
        virtual Move make_move() override;        
};

#endif