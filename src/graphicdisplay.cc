#include "graphicdisplay.h"
#include "window.h"
#include "board.h"
#include <string>
#include <vector>

const int SQUARE_SIZE = 60;
const int PIECE_SIZE = 100;
const int BOARD_SIZE = 8;

GraphicDisplay::GraphicDisplay(Board *board_subject) : 
    board_subject{board_subject},
    screen{SQUARE_SIZE * BOARD_SIZE, SQUARE_SIZE * BOARD_SIZE}
{
    board_subject->attach(this);
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
            drawPieceAt(file, rank);
            // screen.drawString(i * SQUARE_SIZE + SQUARE_SIZE / 2, j * SQUARE_SIZE + SQUARE_SIZE / 2, std::string(1, pieceLetter));
        }
    }
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
    std::vector<std::pair<char, int>> changedBoxes = board_subject->getChangedBoxes();
    for (auto square : changedBoxes) {
        int i = square.first - 'a';
        int j = 8 - square.second;

        int square_colour;
        if ((i + j) % 2 == 0) {
            square_colour = Xwindow::Orange;
        } else {
            square_colour = Xwindow::Brown;
        }
        screen.fillRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, square_colour);
        drawPieceAt(square.first, square.second);
    }
}

void GraphicDisplay::drawPieceAt(char file, int rank) {
    auto piece = board_subject->getPieceAt(file, rank);
    auto pieceColour = piece->getColour();
    auto pieceType = piece->getType();

    int x = (file - 'a') * SQUARE_SIZE;
    int y = (8 - rank) * SQUARE_SIZE;
    int piece_colour = convert(pieceColour);

    if (pieceType == Piece::PieceType::King) {
        drawKing(x, y, piece_colour);
    } else if (pieceType == Piece::PieceType::Queen) {
        drawQueen(x, y, piece_colour);
    } else if (pieceType == Piece::PieceType::Bishop) {
        drawBishop(x, y, piece_colour);
    } else if (pieceType == Piece::PieceType::Rook) {
        drawRook(x, y, piece_colour);
    } else if (pieceType == Piece::PieceType::Knight) {
        drawKnight(x, y, piece_colour);
    } else if (pieceType == Piece::PieceType::Pawn) {
        drawPawn(x, y, piece_colour);
    }
}

GraphicDisplay::~GraphicDisplay() {
    board_subject->detach(this);
    // as for screen, no need to delete.
}