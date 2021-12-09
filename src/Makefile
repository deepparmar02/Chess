CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = main.o board.o piece.o empty.o pawn.o knight.o bishop.o rook.o queen.o king.o observer.o textdisplay.o graphicdisplay.o subject.o move.o window.o player.o human.o levelOne.o levelTwo.o levelThree.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
