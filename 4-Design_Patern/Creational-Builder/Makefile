CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -I./inc

SRC := src/uart_builder.c main.c
BIN := ../bin/Creational_Builder

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)