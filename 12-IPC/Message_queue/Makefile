BIN_DIR = ../bin

mkbin:
	mkdir -p $(BIN_DIR)

all: mkbin
	gcc task_worker.c -o $(BIN_DIR)/task_worker -lrt
	gcc task_dispatcher.c -o $(BIN_DIR)/task_dispatcher -lrt