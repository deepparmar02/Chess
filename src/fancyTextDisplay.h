#ifndef FANCY_TEXT_DISPLAY_H
#define FANCY_TEXT_DISPLAY_H
#include "observer.h"
class Board;

class FancyTextDisplay : public Observer {
    public:
        explicit FancyTextDisplay(Board *board_subject);
        // Displays the Unicode characters representing the
        // chess pieces.
        // Filled-in pieces are white. Transparent ones are black.
        void notify() override;
        ~FancyTextDisplay();
    private:
        Board *board_subject;
};

#endif
