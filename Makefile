# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

# Set up the compiler
CC = gcc
CFLAGS = -Wall -g -I include

# Set the program name
TARGET :=  tcpip

# Source files and .o file output locations
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))
HEADERS := $(wildcard include/*.h)

.DELETE_ON_ERROR:

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

build/%.o: src/%.c build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir build

clean:
	rm -rf build $(TARGET)