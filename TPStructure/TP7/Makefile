CC=gcc
OPT=-Wall
EXEC=arbreGRD

all : $(EXEC)

$(EXEC): main.o arbreGRD.o
	$(CC) $(OPT) main.c arbreGRD.c arbreGRD.h -o $(EXEC)

clean:
	rm -rf *.o $(EXEC)
