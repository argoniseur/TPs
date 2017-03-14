#makefile pile 
CC=gcc
OPT=-Wall -g
EXEC= pilestat

#compile elt_pile
elt_pile.o: elt_pile.c
	$(CC) -o elt_pile.o -c elt_pile.c $(OPT)
#compile pile
pile.o: pile.c
	$(CC) -o pile.o -c pile.c $(OPT)

#compile main
main : main.c
	$(CC) -o main.o -c main.c $(OPT)
	$(CC) elt_pile.o pile.o main.o -o $(EXEC)

hanoi : hanoi.c
	$(CC) -o hanoi.o -c hanoi.c $(OPT)
	$(CC) elt_pile.o pile.o hanoi.o -o $(EXEC)
#link elt_pile,pile et main


clean:
	rm -rf *.o *.exe *.out $(EXEC)

