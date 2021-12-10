#include "move.h"
#include "board.h"
#include "levelOne.h"
#include <random>
#include <iostream>
using namespace std;

LevelOne::LevelOne(Board &board) : Player{board} {}

Move LevelOne::make_move() {
    auto possible_moves = board.getAllPossibleMoves();
    cout << possible_moves.size() << endl;
    srand(time(0));
    int randNum = rand() % (possible_moves.size());
    return possible_moves[randNum];
}