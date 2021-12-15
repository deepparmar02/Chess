#include "fancyTextDisplay.h"
#include "board.h"
#include <iostream>
using namespace std;

FancyTextDisplay::FancyTextDisplay(Board *board_subject) : board_subject{board_subject} {
    board_subject->attach(this);
}

std::string initializeFancyPiece(Piece::PieceType pieceType, Piece::PieceColour colour) {
    string piece;
    if (colour == Piece::PieceColour::Black) {
        if (pieceType == Piece::PieceType::King) {
            piece = "\u2654 ";
        } else if (pieceType == Piece::PieceType::Queen) {
            piece = "\u2655 ";
        } else if (pieceType == Piece::PieceType::Rook) {
            piece = "\u2656 ";
        } else if (pieceType == Piece::PieceType::Bishop) {
            piece = "\u2657 ";
        } else if (pieceType == Piece::PieceType::Knight) {
            piece = "\u2658 ";
        } else {
            piece = "\u2659 ";
        }
    } else {
        if (pieceType == Piece::PieceType::King) {
            piece = "\u265a ";
        } else if (pieceType == Piece::PieceType::Queen) {
            piece = "\u265b ";
        } else if (pieceType == Piece::PieceType::Rook) {
            piece = "\u265c ";
        } else if (pieceType == Piece::PieceType::Bishop) {
            piece = "\u265d ";
        } else if (pieceType == Piece::PieceType::Knight) {
            piece = "\u265e ";
        } else {
            piece = "\u265f ";
        }
    }
    return piece;
}

void FancyTextDisplay::notify() {
    // start with top right square being the Piece::PieceColour::white square
    for (int i = 8; i >= 1; i--) {
        int startWithWhite = 0;
        if (i % 2 != 0) startWithWhite = 1; 
        
        std::cout << i << " ";
        for (char j = 'a'; j <= 'h'; j++) {
            Piece * piece = board_subject->getPieceAt(j, i);
            if (piece->getType() != Piece::PieceType::Empty) {
                std::cout << initializeFancyPiece(piece->getType(), piece->getColour());
            } else {
                if ((j - 'a') % 2 == startWithWhite) {
                    std::cout << "__";
                } else {
                    std::cout << "  ";
                }
            }
        }
        std::cout << endl;
    }

    std::cout << endl;
    std::cout << "  a b c d e f g h" << endl;
    std::cout << endl;
}

FancyTextDisplay::~FancyTextDisplay() {
    board_subject->detach(this);
}