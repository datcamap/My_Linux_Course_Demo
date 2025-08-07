CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g -I./actuator -I./sensor -I./system_config
CFLAGS_RELEASE = -Wall -Wextra -pedantic -O3 -I./actuator -I./sensor -I./system_config

SRCS = 	main.c\
		$(wildcard actuator/*.c) \
		$(wildcard sensor/*.c) \
		$(wildcard system_config/*.c)

TARGET_DEBUG = ../bin/Variable_and_Data_Types_Debug
TARGET_RELEASE = ../bin/Variable_and_Data_Types_Release

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) $(SRCS)

all: all_debug all_release

clean:
	rm -f $(TARGET)

.PHONY: all clean