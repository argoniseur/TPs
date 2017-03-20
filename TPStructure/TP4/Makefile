# @file
# @author Pierre-Antoine Morin
# @brief Configuration file for make

CC := gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic
CFLAGS += -g -O0 # Debug
# CFLAGS += -s -O2 -DNDEBUG # Release

LD := gcc
LDFLAGS =
LDDIRS =
LDLIBS =

SRCDIR = .
OBJDIR = obj
BINDIR = bin

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
EXEC = $(BINDIR)/program

DOCDIR = html

RM := rm -rf
MD := mkdir -p

VALGRIND := valgrind

DOXYGEN := doxygen
DOXYFILE = Doxyfile

.PHONY : all test doc clean clear

all : $(OBJFILES) $(EXEC)

test :
	$(VALGRIND) $(EXEC)

doc : $(DOXYFILE)
	$(DOXYGEN) $<

clean :
	$(RM) $(OBJDIR) $(BINDIR)

clear : clean
	$(RM) $(DOCDIR)

$(EXEC) : $(OBJFILES) | $(BINDIR)
	$(LD) $(LDFLAGS) $(LDDIRS) $^ -o $@ $(LDLIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR) $(BINDIR) :
	$(MD) $@

