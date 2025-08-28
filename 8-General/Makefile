INC = ./inc
SRC = ./src
BIN = ./bin
OBJS = $(BIN)/objs
STATIC_LIB = $(BIN)/static_lib
SHARED_LIB = $(BIN)/shared_lib

all: static shared

static:
	gcc -g -c main.c -o $(OBJS)/main.o -I $(INC)
	gcc -g -c $(SRC)/strultils.c -o $(OBJS)/strultils_static.o -I $(INC)
	ar rcs $(STATIC_LIB)/libstrultils.a $(OBJS)/strultils_static.o
	gcc -static $(OBJS)/main.o -L$(STATIC_LIB) -lstrultils -o $(BIN)/main_static

shared:
	gcc -g -c main.c -o $(OBJS)/main.o -I $(INC)
	gcc -g -c -fPIC $(SRC)/strultils.c -o $(OBJS)/strultils_shared.o -I $(INC)
	gcc -shared $(OBJS)/strultils_shared.o -o $(SHARED_LIB)/libstrultils.so
	gcc $(OBJS)/main.o -L$(SHARED_LIB) -lstrultils -o $(BIN)/main_shared

clean:
	rm -rf $(OBJS)/* $(STATIC_LIB)/* $(SHARED_LIB)/* $(BIN)/main_static $(BIN)/main_shared
