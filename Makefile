CC = clang
# CFLAGS = -std=c11 -Wall -ggdb3 -Wextra -Werror -Wpedantic
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJ_DIR = obj
SRC_DIR = src
LIB_DIR = libmx
LIB_NAME = $(LIB_DIR)/libmx.a
LIB = $(LIB_NAME)
PATHFINDER = pathfinder

SRC = $(SRC_DIR)/*.c
OBJS = $(OBJ_DIR)/*.o

all: $(LIB) $(PATHFINDER)

$(PATHFINDER):
	mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC)
	mv *.o $(OBJ_DIR)
	$(CC) -o $(PATHFINDER) $(OBJS) -L $(LIB_DIR) $(LIB_NAME)

$(LIB):
	make -sC $(LIB_DIR)

clean:
	rm -f $(OBJS)
	rm -df $(OBJ_DIR)

uninstall:
	make -sC $(LIB_DIR) $@
	make clean
	rm -f $(PATHFINDER)

reinstall:
	make uninstall
	make all