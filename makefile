# DEPRECATED
# USE CMAKELISTS.TXT INSTEAD

#g++ main.cpp ./glad/src/glad.c -I./glad/include -o prog.exe -lmingw32 -lSDL2main -lSDL2

#SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
#OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES)) $(BIN_DIR)/glad.o

#Compilier
CC = g++ 
# Directories
SRC_DIR = ./src ./glad/src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Output
BIN_OUTPUT = ./bin/Super-Sweeper-v77.exe
# Sources
SRC_FILES = ./src/main.c ./glad/src/glad.c

# Flags
CFLAGS = -I./glad/include
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -static-libgcc -static-libstdc++
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(BIN_OUTPUT): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@ $(LDFLAGS) -O3

($OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

($OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*

.PHONY: $(BIN_OUTPUT) clean