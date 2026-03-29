CC = clang
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lcs50 -lqrcodegen

SRC = main.c TinyPngOut.c
EXEC = main

ifeq ($(OS),Windows_NT)
	EXEC := $(EXEC).exe
	RM = del /f /q
else
	RM = rm -f
endif

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)

clean:
	$(RM) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run