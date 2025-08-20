CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra

SRC := main.c dec_crc16.c dec_log.c dec_rle.c dec_xor.c raw_loopback.c
BIN := ../bin/Structural-Decorator

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)