CC=gcc
EXEC=grape.out
GRUPO=G1
NTAR=2

SRC_DIR=src
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDE=-I./incs/
LIBS= -lm

CFLAGS=-Wall -Wextra -Wpedantic -O3 -g
LDFLAGS= -Wall -lm

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC) $(OBJ_FILES) $(INCLUDE) $(LIBS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

.PHONY: clean folders send
clean:
	rm -f $(OBJ_FILES)
	rm -fr build/*
	rm -fr docs/doxygen/
	rm -fr docs/Latex/build/

folders:
	mkdir -p src obj incs build docs

#doc:
#doxygen

database:
	cp -r resources/data build/


run:
	@./build/$(EXEC) -h

send:
	tar czf $(GRUPO)-$(NTAR).tgz --transform 's,^,$(GRUPO)-$(NTAR)/,' Makefile src incs docs
