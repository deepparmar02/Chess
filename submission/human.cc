#include "human.h"
#include "board.h"
#include "move.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Human::Human(Board &board) : Player{board} {}

Move Human::make_move() {
    string s;
    getline(cin, s);
    istringstream ss{s};
    string position;
    int i = 0;
            
    // stores all columns (cols[0] is start column, cols[1] is end column)
    vector<char> cols;

    // stores all rows (rows[0] is start column, rows[1] is end row)
    vector<int> rows;

    // stores newPiece inputted for pawn promotion
    char newPiece;
    
    while (ss >> position) {
        istringstream ss1{position};
        i++;
        // if 3 strings (i==2) are inputted for move command
        // then this is pawn promotion move
        if (i == 3) {
            ss1 >> newPiece;
            break;
        }
        char col;
        int row;
        ss1 >> col;
        ss1 >> row;
        cols.push_back(col);
        rows.push_back(row);
    }
    if (cols.size() != 2 || rows.size() != 2) {
        throw NoMove{"Invalid number of arguments"};
    }
    if (i < 3) {
        newPiece = ' ';
    }
    Move move{cols[0], rows[0], cols[1], rows[1], newPiece};
    return move;
}