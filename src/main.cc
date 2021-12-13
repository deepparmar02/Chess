#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "board.h"
#include "observer.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "fancyTextDisplay.h"

#include "player.h"
#include "human.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "move.h"
using namespace std;

int main() {
    Board board{};

    std::unique_ptr<Observer> terminal_display;

    string response;
    cout << "Enable fancy display?(y/n)" << endl;
    cin >> response;
    if (response == "y") {
       terminal_display = std::make_unique<FancyTextDisplay>(&board);
    } else{
       terminal_display = std::make_unique<TextDisplay>(&board);
    }

    GraphicDisplay graphic{&board};

    std::vector<std::unique_ptr<Player>> players(2);
    int turn = 0; // 0 = white, 1 = black
    string command;
    while (cin >> command) {
        if (command == "game") {
            // string whitePlayer, blackPlayer;
            // cin >> whitePlayer >> blackPlayer;
            bool isValidPlayer = true;

            for (int i = 0; i <= 1; i++) {
                string player;
                cin >> player;
                if (player == "computer1") {
                        players[i] = std::make_unique<LevelOne>(board);
                } else if (player == "computer2") {
                    players[i] = std::make_unique<LevelTwo>(board);
                } else if (player == "computer3") {
                    players[i] = std::make_unique<LevelThree>(board);
                } else if (player == "human"){
                    players[i] = std::make_unique<Human>(board);
                } else {
                    cout << "Invalid Command - Must be either human or computer[1-4]" << endl;
                    isValidPlayer = false;
                    break;
                }
            }

            if (isValidPlayer) {
                if (!board.isCustomBoard()) {
                    board.defaultSetup();
                    turn = 0; // default setup means white plays first.
                }
                board.setGameRunning();
                board.notifyObservers();
            }
        }
        else if (command == "resign" || command == "r") {
            if (!board.isGameRunning()) {
                cout << "Game is currently not running." << endl;
                continue;
            }
            board.resign();
            if(board.current_turn() == Piece::PieceColour::White){
                cout << "Black ";
            }else{
                cout << "White ";
            }
            cout << "wins!" << endl;
            turn = 0;
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
                    if (board.current_turn() == Piece::PieceColour::White) {
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
                    if (board.current_turn() == Piece::PieceColour::White) {
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
            turn = 0; // apparently by default, when you enter setup mode
            // the default is that it's white's turn.
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
                    if ("white" == colour) {
                        turn = 0; // if white, we use 1st player ptr
                    } else if ("black" == colour) {
                        turn = 1; // if black, we use 2nd player ptr
                    } else {
                        cout << "Invalid colour" << endl;
                    }
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
    cout << "White: " << board.getScore1() << endl;
    cout << "Black: " << board.getScore2() << endl;
}