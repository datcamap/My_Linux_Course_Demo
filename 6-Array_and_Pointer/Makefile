CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g
CFLAGS_RELEASE = -Wall -Wextra -pedantic -O3

SRCS = main2.c

TARGET_DEBUG = ../bin/double_linked_list_Debug
TARGET_RELEASE = ../bin/double_linked_list_Release

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) $(SRCS)

all: all_debug all_release

clean:
	rm -f $(TARGET)

.PHONY: all clean