CC = clang
CFLAGS = -Wall -Wextra
LDFLAGS = -lcs50

SRC = Download_YT_Links.c
EXEC = Download_YT_Links

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