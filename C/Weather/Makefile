CC = clang
CFLAGS = -Wall -Wextra
LDFLAGS = -lcs50 -lcurl -ljson-c

SRC = Weather.c
EXEC = Weather

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