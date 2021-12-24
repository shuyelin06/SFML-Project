# Compiler
CC := g++
# Compiler Flags
CFLAGS := -Wall -g
# Working Directory
WORKING_DIRECTORY := $(shell pwd)

# Include Paths
INCLUDE := -I"$(WORKING_DIRECTORY)\include"
# Library Paths
LFLAGS := -L"$(WORKING_DIRECTORY)\libs\SFML-2.5.1"
# Library Files
LIBS := -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system

# Folders
BIN := ./bin
OBJ := $(BIN)/obj

SRC := ./src


# Basic Structure (makefiles are whitespace sensitive)
# target: dependencies
# [Tab] action

# Primary Target
$(BIN)/main: $(OBJ)/main.o $(OBJ)/PhysicsObject.o
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BIN)/main.exe $(OBJ)/main.o $(OBJ)/PhysicsObject.o $(LIBS)
	./bin/main

# Dependencies for main.o
$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRC)/main.cpp -o $(OBJ)/main.o

# Dependencies for PhysicsObject
$(OBJ)/PhysicsObject.o: $(SRC)/PhysicsObject.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRC)/PhysicsObject.cpp -o $(OBJ)/PhysicsObject.o

# No dependencies; * is a wildcard (ALL of some file)
.PHONY: clean run
clean:
	rm $(BIN)/main
	rm $(OBJ)/*.o
run:
	$(BIN)/main.exe
