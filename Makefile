#OBJS specifies which files to compile as part of the project
SRC = grid.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++0x 

# LIBS
LIBS=-I/usr/include/SDL2

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lpthread

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = grid

#This is the target that compiles our executable
all : $(SRC)
	$(CC) $(SRC) $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
