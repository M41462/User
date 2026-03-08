# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lraylib  # Windows flags (adjust for Linux)

# Source files (all .cpp files in the project)
SRC = $(wildcard *.cpp)
EXEC = main.exe
# Default target: compile everything at once
all:
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

# Clean the executable
clean:
	del /f /q $(EXEC).exe 2>nul || true  # Windows
	# For Linux, use: rm -f $(EXEC)

# Run the program
run: all
	./$(EXEC)

.PHONY: all clean run
