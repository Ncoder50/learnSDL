# Files
OBJS = learn.cpp

# Compiler
CC = g++

# Compiler flags
COMPILER_FLAGS = -w

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Executable
OBJ_NAME = run

# Compilation
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)