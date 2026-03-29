CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lraylib -lm

SRC = $(wildcard *.cpp)
EXEC = main

ifeq ($(OS),Windows_NT)
	EXEC := $(EXEC).exe
	RM = del /f /q
else
	RM = rm -f
endif

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)

clean:
	$(RM) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run