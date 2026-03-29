CC = clang
CFLAGS = -Wall -Wextra

SRC = main.c
EXEC = interpreter

ifeq ($(OS),Windows_NT)
	EXEC := $(EXEC).exe
	RM = del /f /q
else
	RM = rm -f
endif

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	$(RM) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run