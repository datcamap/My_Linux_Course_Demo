CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -Iinc
LDFLAGS := 

SRC := \
  src/music_player.c \
  src/states/stopped_state.c \
  src/states/playing_state.c \
  src/states/paused_state.c \
  src/states/buffering_state.c \
  src/main.c

BIN := music_player

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
