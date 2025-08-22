CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -I./inc

SRC := 	main.c \
		./src/lighting_driver_mock.c \
		./src/security_driver_mock.c \
		./src/hvac_driver_mock.c \
		./src/smart_home_facade.c
BIN := ../bin/Structural-Facade

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)