CC = gcc

CFLAGS_DEBUG = -Wall -Wextra -pedantic -g -I./src -I./inc -I.
CFLAGS_RELEASE = -Wall -Wextra -pedantic -O3 -I./src -I./inc -I.

SRCS = 	main.c\
		publisher.c\
		subscriber.c\
		$(wildcard src/*.c)

TARGET_DEBUG = ../bin/Observer_Debug
TARGET_RELEASE = ../bin/Observer_Release

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) $(SRCS)

all: all_debug all_release

clean:
	rm -f $(TARGET)

.PHONY: all clean