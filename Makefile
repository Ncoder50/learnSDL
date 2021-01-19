# Files
OBJS = pacman.cpp

# Compiler
CC = g++

# Compiler flags
COMPILER_FLAGS = -w

# Linker flags
LINKER_FLAGS = -lSDL2

# Executable
OBJ_NAME = pacman

# Compilation
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)