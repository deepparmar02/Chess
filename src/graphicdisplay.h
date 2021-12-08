#ifndef GRAPHIC_DISPLAY_H
#define GRAPHIC_DISPLAY_H
#include "observer.h"
#include "window.h"
#include <memory>
class Board;

class GraphicDisplay : public Observer {
    public:
        explicit GraphicDisplay(Board *board_subject);
        void notify() override;
        ~GraphicDisplay();
    private:
        Board *board_subject;
        // what else to add? maybe XWindow maybe?
        Xwindow screen;
};

#endif
