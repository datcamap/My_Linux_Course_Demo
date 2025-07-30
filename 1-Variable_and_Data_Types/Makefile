CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -I./actuator -I./sensor -I./systemConfig

SRCS = 	main.c\
		$(wildcard actuator/*.c) \
		$(wildcard sensor/*.c) \
		$(wildcard systemConfig/*.c)

TARGET = ../bin/1-Variable_and_Data_Types

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean