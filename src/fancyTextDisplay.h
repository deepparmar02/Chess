#ifndef FANCY_TEXT_DISPLAY_H
#define FANCY_TEXT_DISPLAY_H
#include "observer.h"
class Board;

class FancyTextDisplay : public Observer {
    public:
        explicit FancyTextDisplay(Board *board_subject);
        void notify() override;
        ~FancyTextDisplay();
    private:
        Board *board_subject;
};

#endif
