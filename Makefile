SRC = grid.c

CC = gcc

COMPILER_FLAGS = -Wall

LIBS=-I/usr/include/SDL2

LINKER_FLAGS = -lSDL2 -lpthread

EXE_NAME = grid

all : $(SRC)
	$(CC) $(SRC) $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)
