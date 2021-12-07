#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include "observer.h"
class Board;

class TextDisplay : public Observer {
    public:
        explicit TextDisplay(Board *board_subject);
        void notify() override;
        ~TextDisplay();
    private:
        Board *board_subject;
};

#endif
