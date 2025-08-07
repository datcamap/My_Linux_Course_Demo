CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g -I../2-Standard_IO
CFLAGS_RELEASE = -Wall -Wextra -pedantic -O3 -I../2-Standard_IO

SRCS = main.c led_driver.c ../2-Standard_IO/logger.c

TARGET_DEBUG = ../bin/Operator_and_Control_Structures_Debug
TARGET_RELEASE = ../bin/Operator_and_Control_Structures_Release

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) $(SRCS)

all: all_debug all_release

clean:
	rm -f $(TARGET)

.PHONY: all clean