CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic  -g
LDFLAGS = -lraylib

SRC = main.cpp Player.cpp Quiz.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = ../Src/game.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
