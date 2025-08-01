CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g -I./actuator -I./sensor -I./system_config
CFLAGS_RELEASE = -Wall -Wextra -pedantic -I./actuator -I./sensor -I./system_config

SRCS = 	main.c\
		$(wildcard actuator/*.c) \
		$(wildcard sensor/*.c) \
		$(wildcard system_config/*.c)

TARGET = ../bin/1-Variable_and_Data_Types

all_debug:
	$(CC) $(CFLAGS_DEBUG) -o $(TARGET) $(SRCS)

all_release:
	$(CC) $(CFLAGS_RELEASE) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean