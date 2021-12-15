#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
class Move;
class Board;

class Human : public Player {
    public:
        explicit Human(Board &board);

        /** Human's make_move reads from stdin and
         * based off the arguments read, creates a Move object.
         * 
         * However, if there are not enough arguments, it 
         * throws a NoMove exception.
         *
         * If it does throw, the Board object inside is untouched.
         */
        virtual Move make_move() override;
};

#endif