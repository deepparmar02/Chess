#include "graphicdisplay.h"
#include "window.h"
#include "board.h"

const int SQUARE_SIZE = 50;
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
                colour = Xwindow::Black;
            }

            screen.fillRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, colour);

            int rank = 8 - j;
            char file = 'a' + i;

            auto piece = board_subject->getPieceAt(file, rank);

            // here, we do some logic. We draw the piece depending on
            // what type of piece and colour it is. Haven't done that yet. We can all work on it together.

        }
    }
}

GraphicDisplay::~GraphicDisplay() {
    board_subject->detach(this);
    // as for screen, no need to delete.
}