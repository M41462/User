CC = clang
# Use --driver-mode=cl to match your .clangd settings
CFLAGS = --driver-mode=cl -Wall -Wextra -g

# vcpkg path configuration
VCPKG_ROOT = C:/Users/Ilyes/vcpkg/installed/x64-windows
VCPKG_INC  = /I"$(VCPKG_ROOT)/include"
VCPKG_LIB  = /link /LIBPATH:"$(VCPKG_ROOT)/lib"

# Source files (Added qrcodegen.c since it's in your current directory)
SRC = main.c TinyPngOut.c qrcodegen.c
EXEC = main

ifeq ($(OS),Windows_NT)
    EXEC := $(EXEC).exe
    RM = del /f /q
    # Windows Linker flags (vcpkg libs + windows system libraries if needed)
    LDFLAGS = $(VCPKG_LIB) cs50.lib
    INCLUDES = $(VCPKG_INC) /I"."
else
    RM = rm -f
    LDFLAGS = -lcs50 -lqrcodegen
    INCLUDES =
endif

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(EXEC) $(LDFLAGS)

clean:
	$(RM) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run
