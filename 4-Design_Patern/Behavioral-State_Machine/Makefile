CC      := gcc
CFLAGS  := -std=c11 -g -Wall -Wextra -I./inc -I./inc/states
LDFLAGS := 

SRC := main.c \
  src/music_player.c \
  src/states/stopped_state.c \
  src/states/playing_state.c \
  src/states/paused_state.c \
  src/states/buffering_state.c

BIN := ../bin/music_player

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
