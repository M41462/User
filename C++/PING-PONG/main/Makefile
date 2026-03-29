CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

SRCS = main.cpp ../Include/UI.cpp ../Include/Game.cpp ../Include/Data.cpp
EXEC = main

ifeq ($(OS),Windows_NT)
	EXEC := $(EXEC).exe
	RM = del /f /q
else
	RM = rm -f
endif

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(LDFLAGS)

clean:
	$(RM) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run