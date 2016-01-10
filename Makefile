SHELL=/bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o
CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lz
SOURCES=Driver.cpp Board.cpp BoardQ.cpp bfs.cpp
HEADERS=Board.h BoardQ.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rush_hour_solver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -Wall -std=c++11 $(OBJECTS) $(LDFLAGS) -o $@ 

Driver.o: Driver.cpp
	$(CC) $(CFLAGS) Driver.cpp

Board.o: Board.cpp Board.h
	$(CC) $(CFLAGS) Board.cpp

BoardQ.o: BoardQ.cpp BoardQ.h
	$(CC) $(CFLAGS) BoardQ.cpp

bfs.o: bfs.cpp
	$(CC) $(CFLAGS) bfs.cpp


#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o rush_hour_solver
