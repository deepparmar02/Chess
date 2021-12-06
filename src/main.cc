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

            if (!board.isCustomBoard()) {
                board.defaultSetup();
            }
            board.setGameRunning();
        }
        else if (command == "resign") {
            // reinitialize board/destroy board
            // update scoreboard
        }
        else if (command == "move") {
            if (!board.isGameRunning()) {
                cout << "Game is currently not running." << endl;
                continue;
            }
            string s;
            getline(cin, s);  // read rest of line from input
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

            bool valid_move = false;
            if (i == 3) {
                // call pawn promotion move overload method
            } else {
                valid_move = board.move(cols[0], rows[0], cols[1], rows[1]);
            }
            cout << board << endl;

            if (valid_move) {
                if (board.inCheckmate()) {
                    cout << "Checkmate! ";
                    if (board.whose_turn == Piece::PieceColour::White) {
                        cout << "Black";
                    } else {
                        cout << "White";
                    }
                    cout << " wins" << endl;
                }
                else if (board.inStalemate()) {
                    cout << "Stalemate" << endl;
                }
                else if (board.inCheck()) {
                    if (board.whose_turn == Piece::PieceColour::White) {
                        cout << "White";
                    } else {
                        cout << "Black";
                    }
                    cout << " is in check." << endl;
                }
            }
        }
        else if (command == "setup") { 
            if (board.isGameRunning()) {
                cout << "Game is currently running." << endl;
                continue;
            }
            board.enterSetupMode();
            string setupCmd;
            while (cin >> setupCmd) {
                if (setupCmd == "+") {
                    char piece, col;
                    int row;
                    cin >> piece >> col >> row;

                    board.addPiece(col, row, piece);
                    cout << board << endl;
                }
                else if (setupCmd == "-") {
                    char col;
                    int row;
                    cin >> col >> row;

                    board.deletePiece(col, row);
                    cout << board << endl;
                }
                else if (setupCmd == "=") {
                    string colour;
                    cin >> colour;

                    board.changeColour(colour);
                }
                else if (setupCmd == "done") {
                    // check for board validity before quitting
                    if (board.endSetupMode()) {
                        break;
                    } 
                    cout << "Invalid board" << endl;
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