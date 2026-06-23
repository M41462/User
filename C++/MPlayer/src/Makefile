CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../include
LDFLAGS = -lsfml-audio-3 -lsfml-graphics-3 -lsfml-window-3 -lsfml-system-3

SRC = main.cpp ../include/UI.cpp ../include/MP.cpp ../include/Visual.cpp
EXEC = music_player

ifeq ($(OS),Windows_NT)
	EXEC := $(EXEC).exe
	RM = del /f /q
	LDFLAGS += -lcomdlg32
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