CC      := gcc
CFLAGS  := -std=c11 -g -Wall -Wextra -I./inc

SRC := 	main.c \
		./src/dec_crc16.c \
		./src/dec_log.c \
		./src/dec_rle.c \
		./src/dec_xor.c \
		./src/raw_loopback.c
BIN := ../bin/Structural-Decorator

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)