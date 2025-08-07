CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g
CFLAGS_RELEASE = -Wall -Wextra -pedantic -O3

SRCS = main.c logger.c

TARGET_DEBUG = ../bin/Standard_IO_Debug
TARGET_RELEASE = ../bin/Standard_IO_Release

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) $(SRCS)

all: all_debug all_release

clean:
	rm -f $(TARGET)

.PHONY: all clean