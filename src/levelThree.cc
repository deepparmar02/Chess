#include "move.h"
#include "board.h"
#include "levelThree.h"
#include <random>

LevelThree::LevelThree(Board &board) : Player{board} {}

Move LevelThree::make_move() {
    auto possible_moves = board.getAvoidCapturingMoves();
    if (possible_moves.empty()) {
        possible_moves = board.getCheckMoves();
    }
    if (possible_moves.empty()) {
        possible_moves = board.getAllCapturingMoves();
    }
    if (possible_moves.empty()) {
        possible_moves = board.getAllPossibleMoves();
    }
    srand(time(0));
    int randNum = rand() % (possible_moves.size());
    return possible_moves[randNum];
}