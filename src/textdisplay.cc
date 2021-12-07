#include "textdisplay.h"
#include <iostream>
#include "board.h"
#include "piece.h" // for now.
// just in case 
#include "empty.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
// end of just in case
using namespace std;

TextDisplay::TextDisplay(Board *board_subject) : board_subject{board_subject} {
    board_subject->attach(this);
}

char initializeBoardPiece(Piece::PieceType pieceType, Piece::PieceColour colour) {
    char piece;
    if (pieceType == Piece::PieceType::King) {
        piece = 'K';
    } else if (pieceType == Piece::PieceType::Queen) {
        piece = 'Q';
    } else if (pieceType == Piece::PieceType::Rook) {
        piece = 'R';
    } else if (pieceType == Piece::PieceType::Bishop) {
        piece = 'B';
    } else if (pieceType == Piece::PieceType::Knight) {
        piece = 'N';
    } else {
        piece = 'P';
    }

    // if Black piece, then change to lower case
    if (colour == Piece::PieceColour::Black) {
        piece = tolower(piece);
    }
    return piece;
}

void TextDisplay::notify() {
    // start with top right square being the Piece::PieceColour::white square
    for (int i = 8; i >= 1; i--) {
        int startWithWhite = 0;
        if (i % 2 != 0) startWithWhite = 1; 
        
        std::cout << i << " ";
        for (char j = 'a'; j <= 'h'; j++) {
            Piece * piece = board_subject->getPieceAt(j, i);
            if (piece->getType() != Piece::PieceType::Empty) {
                std::cout << initializeBoardPiece(piece->getType(), piece->getColour());
            } else {
                if ((j - 'a') % 2 == startWithWhite) {
                    std::cout << "_";
                } else {
                    std::cout << " ";
                }
            }
        }
        std::cout << endl;
    }

    std::cout << endl;
    std::cout << "  abcdefgh" << endl;
}

TextDisplay::~TextDisplay() {
    board_subject->detach(this);
}