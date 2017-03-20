BASH=/bin/bash
# le nom de l'executable (source dans $(TARGET).c)
TARGET=skiplisttest
# liste des fichiers sources à utiliser

SOURCES=$(TARGET).c skiplist.c rng.c

# definitions generales
OBJECTS=$(SOURCES:.c=.o)

# parametres du compilateur -- Doit absolument etre gcc
CC=gcc
CFLAGS+=-g -std=c99 -Wextra -Wall -pedantic-errors -Werror

#regles de construction du programme
$(TARGET) :  $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o :
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(TARGET)  $(OBJECTS) *~

doc :
	doxygen docparameters

tests : $(TARGET)
	@$(BASH) test_script.sh

# dependances
rng.o : rng.h
skiplist.o : skiplist.h rng.h
$(TARGET).o : skiplist.h rng.h
doc : rng.h skiplist.h
