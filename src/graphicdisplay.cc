#include "graphicdisplay.h"
#include "window.h"
#include "board.h"
#include <string>

const int SQUARE_SIZE = 50;
const int PIECE_SIZE = 100;
const int BOARD_SIZE = 8;

GraphicDisplay::GraphicDisplay(Board *board_subject) : 
    board_subject{board_subject},
    screen{SQUARE_SIZE * BOARD_SIZE, SQUARE_SIZE * BOARD_SIZE}
{
    board_subject->attach(this);
}

void GraphicDisplay::notify() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {

            int colour;
            if ((i + j) % 2 == 0) {
                colour = Xwindow::White;
            } else {
                colour = Xwindow::Green;
            }

            screen.fillRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, colour);

            int rank = 8 - j;
            char file = 'a' + i;

            auto piece = board_subject->getPieceAt(file, rank);
            auto pieceColour = piece->getColour();
            auto pieceType = piece->getType();
            char pieceLetter;

            if (pieceType == Piece::PieceType::King) {
                pieceLetter = 'K';
            } else if (pieceType == Piece::PieceType::Queen) {
                pieceLetter = 'Q';
            } else if (pieceType == Piece::PieceType::Bishop) {
                pieceLetter = 'B';
            } else if (pieceType == Piece::PieceType::Rook) {
                pieceLetter = 'R';
            } else if (pieceType == Piece::PieceType::Knight) {
                pieceLetter = 'N';
            } else if (pieceType == Piece::PieceType::Pawn) {
                pieceLetter = 'P';
            } else {
                pieceLetter = ' ';
            }

            if (pieceColour == Piece::PieceColour::Black) {
                pieceLetter = tolower(pieceLetter);
            }

            screen.drawString(i * SQUARE_SIZE + SQUARE_SIZE / 2, j * SQUARE_SIZE + SQUARE_SIZE / 2, std::string(1, pieceLetter));
        }
    }
}

GraphicDisplay::~GraphicDisplay() {
    board_subject->detach(this);
    // as for screen, no need to delete.
}