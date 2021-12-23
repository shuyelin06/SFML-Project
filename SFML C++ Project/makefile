# Compiler
CC := g++
# Compiler Flags
CFLAGS := -Wall -g
# Working Directory
WORKING_DIRECTORY := $(shell pwd)

# Include Paths
INCLUDE := -I"$(WORKING_DIRECTORY)\libs\SFML-2.5.1\include"
# Library Paths
LFLAGS := -L"$(WORKING_DIRECTORY)\libs\SFML-2.5.1\lib" 
# Library Files
LIBS := -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system

# Basic Structure (makefiles are whitespace sensitive)
# target: dependencies
# [Tab] action

# Primary Target
./bin/main: ./bin/obj/main.o
	$(CC) $(CFLAGS) $(LFLAGS) -o ./bin/main.exe ./bin/obj/main.o $(LIBS)
	./bin/main

# Dependencies for main.o
./bin/obj/main.o: ./src/main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c ./src/main.cpp -o ./bin/obj/main.o

# No dependencies; * is a wildcard (ALL of some file)
.PHONY: clean
clean:
	rm ./bin/main
	rm ./bin/obj/*.o
