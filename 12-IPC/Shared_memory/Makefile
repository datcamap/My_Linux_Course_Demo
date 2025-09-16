BIN_DIR = ../bin

mkbin:
	mkdir -p $(BIN_DIR)

all: mkbin
	gcc posix_shm_producer.c -o $(BIN_DIR)/posix_producer
	gcc posix_shm_consumer.c -o $(BIN_DIR)/posix_consumer

main: mkbin
	gcc -g main.c -o $(BIN_DIR)/main