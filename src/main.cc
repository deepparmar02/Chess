#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "board.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "player.h"
#include "human.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "move.h"
using namespace std;

int main() {
    Board board{};

    TextDisplay text{&board};
    // GraphicDisplay graphic{&board};
    // board.notifyObservers();

    std::vector<std::unique_ptr<Player>> players(2);
    int turn = 0; // 0 = white, 1 = black
    string command;
    while (cin >> command) {
        if (command == "game") {
            string whitePlayer, blackPlayer;
            cin >> whitePlayer >> blackPlayer;

            // if any player is an int, then they are computers
            istringstream ss{whitePlayer};
            int whitePlayerLevel, blackPlayerLevel;
            if (ss >> whitePlayerLevel) {
                if (whitePlayerLevel == 1) {
                    players[0] = std::make_unique<LevelOne>(board);
                } else if (whitePlayerLevel == 2) {
                    players[0] = std::make_unique<LevelTwo>(board);
                } else if (whitePlayerLevel == 3) {
                    players[0] = std::make_unique<LevelThree>(board);
                } 
            } else {
                players[0] = std::make_unique<Human>(board);
            }
            ss.clear();
            ss.str(blackPlayer);
            if (ss >> blackPlayerLevel) {
                if (blackPlayerLevel == 1) {
                    players[1] = std::make_unique<LevelOne>(board);
                } else if (blackPlayerLevel == 2) {
                    players[1] = std::make_unique<LevelTwo>(board);
                } else if (blackPlayerLevel == 3) {
                    players[1] = std::make_unique<LevelThree>(board);
                } 
            } else {
                players[1] = std::make_unique<Human>(board);
            }

            if (!board.isCustomBoard()) {
                board.defaultSetup();
            }
            board.setGameRunning();
            board.notifyObservers();
        }
        else if (command == "resign" || command == "r") {
            if (!board.isGameRunning()) {
                cout << "Game is currently not running." << endl;
                continue;
            }
            board.resign();
            if(board.whose_turn == Piece::PieceColour::White){
                cout << "Black ";
            }else{
                cout << "White ";
            }
            cout << "wins!" << endl;
        }
        else if (command == "move" || command == "m") {
            if (!board.isGameRunning()) {
                cout << "Game is currently not running." << endl;
                continue;
            }

            // Human handles input. Computer doesn't need to.
            Move move_made = players[turn]->make_move();
            // if promote move
            bool valid_move = board.move(move_made);

            board.notifyObservers();
            if (valid_move) {
                turn = (turn + 1) % 2; // change turns
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
        else if (command == "setup" || command == "s") { 
            if (board.isGameRunning()) {
                cout << "Game is currently running." << endl;
                continue;
            }
            board.notifyObservers();
            board.enterSetupMode();
            string setupCmd;
            while (cin >> setupCmd) {
                if (setupCmd == "+") {
                    char piece, col;
                    int row;
                    cin >> piece >> col >> row;

                    board.addPiece(col, row, piece);
                    board.notifyObservers();
                }
                else if (setupCmd == "-") {
                    char col;
                    int row;
                    cin >> col >> row;

                    board.deletePiece(col, row);
                    board.notifyObservers();
                }
                else if (setupCmd == "=") {
                    string colour;
                    cin >> colour;

                    board.changeColour(colour);
                }
                else if (setupCmd == "done" || setupCmd == "d") {
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

    cout << "Final Score:" << endl;
    cout << "White: " << board.getScore1()<< endl;
    cout << "Black: " << board.getScore2() << endl;
}