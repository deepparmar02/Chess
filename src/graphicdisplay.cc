#include "graphicdisplay.h"
#include "board.h"

GraphicDisplay::GraphicDisplay(Board *board_subject) : board_subject{board_subject} {
    board_subject->attach(this);
}

void GraphicDisplay::notify() {
    // dunno yet.
    return;
}

GraphicDisplay::~GraphicDisplay() {
    board_subject->detach(this);
}