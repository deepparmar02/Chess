#ifndef GRAPHIC_DISPLAY_H
#define GRAPHIC_DISPLAY_H
#include "observer.h"
#include "window.h"
#include "piece.h"
#include <memory>
class Board;

class GraphicDisplay : public Observer {
    public:
        explicit GraphicDisplay(Board *board_subject);
        // Displays the chessboard on an XWindow.
        void notify() override;
        ~GraphicDisplay();
    private:
        Board *board_subject;
        Xwindow screen;

        void drawRook(int x, int y, int colour);
        void drawPawn(int x, int y, int colour);
        void drawBishop(int x, int y, int colour);
        void drawKnight(int x, int y, int colour);
        void drawQueen(int x, int y, int colour);
        void drawKing(int x, int y, int colour);
        void drawPieceAt(char file, int rank);
};

#endif
