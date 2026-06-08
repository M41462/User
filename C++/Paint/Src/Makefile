comma := ,
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../Include
LDFLAGS = -lSDL2 -lSDL2_image -Wl$(comma)--subsystem$(comma)console

SRC = main.cpp UI.cpp Brush.cpp Save.cpp
EXEC = paint

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