.PHONY: all clean maxclean

CC=gcc
CFLAGS=-Wextra -Wall -pedantic-errors -Werror -std=c99
EXEC=rbtree
OBJ=rbtree.o main.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

rbtree.o: rbtree.c
main.o: main.c


clean:
	rm -rf *.o $(EXEC) *.dot *.pdf

