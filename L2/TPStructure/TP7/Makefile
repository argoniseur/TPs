CC=gcc
OPT=-Wall
EXEC=arbreGRD

all: $(EXEC)

$(EXEC): main.o arbreGRD.o queue.o
	$(CC) $(OPT) main.c arbreGRD.c queue.c -o $(EXEC)

clean:
	rm -rf *.o $(EXEC) *.txt
