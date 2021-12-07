#include "textdisplay.h"
#include "board.h"

TextDisplay::TextDisplay(Board *board_subject) : board_subject{board_subject} {
    board_subject->attach(this);
}

void TextDisplay::notify() {
    // dunno yet.
    return;
}

TextDisplay::~TextDisplay() {
    board_subject->detach(this);
}