# Compiler
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -I../Include

# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lSDL2 -lSDL2_image
	RUN_CMD = ./$(EXEC)
endif
ifeq ($(OS),Windows_NT)
	LDFLAGS = -lSDL2 -lSDL2_image
	RUN_CMD = $(EXEC).exe
endif

# Source files
SRCS = Brush.cpp Save.cpp UI.cpp main.cpp
EXEC = paint

# Default target: compile all at once
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(LDFLAGS)

# Clean
clean:
	rm -f $(EXEC) $(EXEC).exe

# Run
run: all
	$(RUN_CMD)

.PHONY: all clean run
