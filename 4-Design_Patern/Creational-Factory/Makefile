CC      := gcc
CFLAGS  := -std=c11 -g -Wall -Wextra -I./inc

SRC := main.c ./src/sensor_factory.c ./src/temp_sensor.c ./src/humidity_sensor.c
BIN := ../bin/Creational_Factory

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)