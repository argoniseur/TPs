.PHONY: all clean maxclean

CC=gcc
CFLAGS=-Wall
EXEC=exo1
OBJ=boucler.o tp23_exo1-v1_base.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

boucler.o: boucler.c
tp23_exo1-v1_base.o: tp23_exo1-v1_base.c


clean:
	rm -rf *.o $(EXEC)
