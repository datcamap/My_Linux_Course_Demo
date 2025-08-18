CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra

SRC := main.c lighting_driver_mock.c security_driver_mock.c hvac_driver_mock.c smart_home_facade.c
BIN := ../bin/Structural-Facade

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)