#include "move.h"
#include "board.h"
#include "levelThree.h"

LevelThree::LevelThree(Board &board) : Player{board} {}

Move LevelThree::make_move() {
    return Move{0, 0, 0, 0, '\0'};
}