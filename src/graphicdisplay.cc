#include "graphicdisplay.h"
#include "window.h"
#include "board.h"
#include <string>

const int SQUARE_SIZE = 60;
const int PIECE_SIZE = 100;
const int BOARD_SIZE = 8;

GraphicDisplay::GraphicDisplay(Board *board_subject) : 
    board_subject{board_subject},
    screen{SQUARE_SIZE * BOARD_SIZE, SQUARE_SIZE * BOARD_SIZE}
{
    board_subject->attach(this);
}

int convert(Piece::PieceColour colour) {
    if (colour == Piece::PieceColour::White) {
        return Xwindow::White;
    } else {
        return Xwindow::Black;
    }
}

// Right now, there is a lot of copied code. I will deal with it later.
// For now, this is a proof of concept.

void GraphicDisplay::drawRook(int x, int y, int colour) {
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 2 / 5, y + SQUARE_SIZE / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 7 / 10, y + SQUARE_SIZE / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 3 / 10, y + SQUARE_SIZE * 3 / 10, SQUARE_SIZE * 2 / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE * 7 / 10, SQUARE_SIZE * 4 / 5, SQUARE_SIZE / 5, colour);
}

void GraphicDisplay::drawPawn(int x, int y, int colour) {
    screen.fillRectangle(x + SQUARE_SIZE * 3 / 10, y + SQUARE_SIZE / 10, SQUARE_SIZE * 2 / 5, SQUARE_SIZE / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 2 / 5, y + SQUARE_SIZE * 3 / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE * 7 / 10, SQUARE_SIZE * 4 / 5, SQUARE_SIZE / 5, colour);
}

void GraphicDisplay::drawBishop(int x, int y, int colour) {
    screen.fillRectangle(x + SQUARE_SIZE * 2 / 5, y + SQUARE_SIZE / 10, SQUARE_SIZE / 5, SQUARE_SIZE / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 3 / 10, y + SQUARE_SIZE * 3 / 10, SQUARE_SIZE * 2 / 5, SQUARE_SIZE / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 2 / 5, y + SQUARE_SIZE / 2, SQUARE_SIZE / 5, SQUARE_SIZE / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE * 7 / 10, SQUARE_SIZE * 4 / 5, SQUARE_SIZE / 5, colour);
}

void GraphicDisplay::drawQueen(int x, int y, int colour) {
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE * 3 / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 7 / 10, y + SQUARE_SIZE * 3 / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 2 / 5, y + SQUARE_SIZE / 10, SQUARE_SIZE / 5, SQUARE_SIZE * 3 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 3 / 10, y + SQUARE_SIZE * 7 / 10, SQUARE_SIZE * 2 / 5, SQUARE_SIZE / 5, colour);
}

void GraphicDisplay::drawKing(int x, int y, int colour) {
    screen.fillRectangle(x + SQUARE_SIZE * 2 / 5, y + SQUARE_SIZE / 10, SQUARE_SIZE / 5, SQUARE_SIZE / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE * 3 / 10, SQUARE_SIZE * 4 / 5, SQUARE_SIZE * 2 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE * 3 / 10, y + SQUARE_SIZE * 7 / 10, SQUARE_SIZE * 2 / 5, SQUARE_SIZE / 5, colour);
}

void GraphicDisplay::drawKnight(int x, int y, int colour) {
    screen.fillRectangle(x + SQUARE_SIZE * 3 / 10, y + SQUARE_SIZE / 10, SQUARE_SIZE * 3 / 10, SQUARE_SIZE * 3 / 5, colour);
    screen.fillRectangle(x + SQUARE_SIZE / 2, y + SQUARE_SIZE / 10, SQUARE_SIZE * 3 / 10, SQUARE_SIZE * 3 / 10, colour);
    screen.fillRectangle(x + SQUARE_SIZE / 10, y + SQUARE_SIZE * 7 / 10, SQUARE_SIZE * 4 / 5, SQUARE_SIZE / 5, colour);
}

void GraphicDisplay::notify() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {

            int square_colour;
            if ((i + j) % 2 == 0) {
                square_colour = Xwindow::Orange;
            } else {
                square_colour = Xwindow::Brown;
            }

            screen.fillRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, square_colour);

            int rank = 8 - j;
            char file = 'a' + i;

            auto piece = board_subject->getPieceAt(file, rank);
            auto pieceColour = piece->getColour();
            auto pieceType = piece->getType();
            char pieceLetter;

            int x = i * SQUARE_SIZE;
            int y = j * SQUARE_SIZE;
            int piece_colour = convert(pieceColour);

            if (pieceType == Piece::PieceType::King) {
                drawKing(x, y, piece_colour);
                pieceLetter = 'K';
            } else if (pieceType == Piece::PieceType::Queen) {
                drawQueen(x, y, piece_colour);
                pieceLetter = 'Q';
            } else if (pieceType == Piece::PieceType::Bishop) {
                drawBishop(x, y, piece_colour);
                pieceLetter = 'B';
            } else if (pieceType == Piece::PieceType::Rook) {
                drawRook(x, y, piece_colour);
                pieceLetter = 'R';
            } else if (pieceType == Piece::PieceType::Knight) {
                drawKnight(x, y, piece_colour);
                pieceLetter = 'N';
            } else if (pieceType == Piece::PieceType::Pawn) {
                drawPawn(x, y, piece_colour);
                pieceLetter = 'P';
            } else {
                pieceLetter = ' ';
            }

            if (pieceColour == Piece::PieceColour::Black) {
                pieceLetter = tolower(pieceLetter);
            }

            // screen.drawString(i * SQUARE_SIZE + SQUARE_SIZE / 2, j * SQUARE_SIZE + SQUARE_SIZE / 2, std::string(1, pieceLetter));
        }
    }
}

GraphicDisplay::~GraphicDisplay() {
    board_subject->detach(this);
    // as for screen, no need to delete.
}