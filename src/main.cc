#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
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
            char row, col;
            int startRow, endRow, startCol, endCol;
            cin >> row >> startCol >> col >> endCol;

            startRow = row - 'a';
            endRow = col - 'a';

            cout << startRow << "-" << startCol << endl;
            cout << endRow << "-" << endCol << endl;

            // call move function
            // need to handle pawn promotion move command

        }
        else if (command == "setup") {
            string setupCmd;
            while (cin >> setupCmd) {
                if (setupCmd == "+") {
                    char piece, charRow;
                    int row, col;
                    cin >> piece >> charRow >> col;

                    row = charRow - 'a';
                }
                else if (setupCmd == "-") {
                    char charRow;
                    int row, col;
                    cin >> charRow >> col;

                    row = charRow - 'a';
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