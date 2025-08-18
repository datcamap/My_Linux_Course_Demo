CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra

SRC := main.c sensor_factory.c temp_sensor.c humidity_sensor.c
BIN := ../bin/Creational_Factory

.PHONY: all clean run
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)