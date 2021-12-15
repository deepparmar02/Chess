#include "move.h"
#include "board.h"
#include "levelOne.h"
#include <random>
#include <iostream>
using namespace std;

LevelOne::LevelOne(Board &board) : Player{board} {}

Move LevelOne::make_move() {
    auto possible_moves = board.getAllPossibleMoves();
    srand(time(0));
    if (possible_moves.size() == 0) {
        throw NoMove{"No moves available"};
    }
    int randNum = rand() % (possible_moves.size());
    return possible_moves[randNum];
}