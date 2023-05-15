CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = src/main.o src/board.o src/piece.o src/empty.o src/pawn.o src/knight.o src/bishop.o src/rook.o src/queen.o src/king.o src/observer.o src/textdisplay.o src/graphicdisplay.o src/fancyTextDisplay.o src/subject.o src/move.o src/window.o src/player.o src/human.o src/levelOne.o src/levelTwo.o src/levelThree.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
