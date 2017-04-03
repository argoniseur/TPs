CC=gcc
CFLAGS=-Wall
OBJ=dequeue_iterator.o dqueue.o unit_test_iterator.o
EXEC=unit_test_iterator
All: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o unit_test_iterator


dequeue_iterator.o: dequeue_iterator.c
dqueue.o: dqueue.c
unit_test_iterator.o: unit_test_iterator.c

clean:
	rm -rf *.o $(EXEC)
