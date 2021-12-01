#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "board.h"
using namespace std;

int main() {
    // cout << "here" << endl;
    Board board{};
    cout << board << endl;
    string command;
    while (cin >> command) {
        if (command == "game") {
            string whitePlayer, blackPlayer;
            cin >> whitePlayer >> blackPlayer;

            cout << whitePlayer << " Vs. " << blackPlayer << endl;

            // if any player is an int, then they are computers
            istringstream ss{whitePlayer};
            int whitePlayerLevel, blackPlayerLevel;
            if (ss >> whitePlayerLevel) cout << "Player 1 is Computer of level " << whitePlayerLevel << endl;
            ss.clear();
            ss.str(blackPlayer);
            if (ss >> blackPlayerLevel) cout << "Player 2 is Computer of level " << blackPlayerLevel << endl;
        

            // initialize board and start game
        }
        else if (command == "resign") {
            // reinitialize board/destroy board
            // update scoreboard
        }
        else if (command == "move") {
            char startCol, endCol;
            int startRow, endRow;
            cin >> startCol >> startRow >> endCol >> endRow;

            board.move(startCol, startRow, endCol, endRow);
            cout << board << endl;
            // need to handle pawn promotion move command

        }
        else if (command == "setup") {
            string setupCmd;
            while (cin >> setupCmd) {
                if (setupCmd == "+") {
                    char piece, col;
                    int row;
                    cin >> piece >> col >> row;
                }
                else if (setupCmd == "-") {
                    char col;
                    int row;
                    cin >> col >> row;
                }
                else if (setupCmd == "done") {
                    // check for board validity before quitting
                    break;
                }
                else {
                   cerr << "Invalid Command" << endl;
                }
            }
        }
        else {
            cerr << "Invalid Command" << endl;
        }
    }
}