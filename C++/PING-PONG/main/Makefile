CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
SOURCES = main.cpp ../Include/UI.cpp ../Include/Game.cpp ../Include/Data.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./main.exe

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
