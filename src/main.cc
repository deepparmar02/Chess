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
            string s;
            getline(cin, s);  // read rest of line from input
            istringstream ss{s};
            string position;
            int i = 0;
            
            // stores all columns (cols[0] is start column, cols[1] is end columns)
            vector<char> cols;  

            // stores all rows (rows[0] is start column, rows[1] is end row)
            vector<int> rows; 

            // stores newPiece inputted for pawn promotion
            char newPiece;
            
            while (ss >> position) {
                istringstream ss1{position};
                // if 3 strings (i==2) are inputted for move command
                // then this is pawn promotion move
                if (i == 2) {
                    ss1 >> newPiece;
                    i++;
                    break;
                } 
                char col;
                int row;
                ss1 >> col;
                ss1 >> row;
                cols.push_back(col);
                rows.push_back(row);
                i++;
            }
        
            if (i == 3) {
                // call pawn promotion move overload method
            } else {
                board.move(cols[0], rows[0], cols[1], rows[1]);
            }
            cout << board << endl;

            if (board.inCheck()) {
                if (board.whose_turn == Piece::PieceColour::White) {
                    cout << "White";
                } else {
                    cout << "Black";
                }
                cout << " is in check." << endl;
            }

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