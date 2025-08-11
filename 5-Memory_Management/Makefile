CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g
CFLAGS_RELEASE = -g -Wall -Wextra -pedantic -O3

SRCS = memory_lab.c

TARGET_DEBUG = ../bin/memery_lab_Debug
TARGET_RELEASE = ../bin/memery_lab_Release

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) $(SRCS)

all: all_debug all_release

clean:
	rm -f $(TARGET)

.PHONY: all clean