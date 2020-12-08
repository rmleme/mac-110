#
# Makefile para trabalhar com gb_flip.c
#
#======================================================================
# Aqui devemos ter o diretório onde estão os arquivos .h 
# das bibliotecas de Roberts 
CSINCDIR = /home/prof/yoshi/Roberts/libraries/standard

# Aqui devemos ter o diretório onde está o arquivo cslib.a
# da biblioteca de Roberts
CSLIBDIR = /home/prof/yoshi/Roberts/libraries/standard
#======================================================================

CC = gcc
CFLAGS = -g -Wall -I. -I$(CSINCDIR)
LDFLAGS = -L. 
LDLIBS = $(CSLIBDIR)/cslib.a -lm

RM = /bin/rm -f

OBJS = gb_flip.o ep3b.o

#======================================================================

gb_flip.o: gb_flip.h gb_flip.c
	$(CC) $(CFLAGS) -c $*.c

ep3b.o: ep3b.c
	$(CC) $(CFLAGS) -c $*.c

ep3b: ep3b.o gb_flip.o
	$(CC) $(LDFLAGS) -o ep3b ep3b.o gb_flip.o $(LDLIBS) 

clean:
	$(RM) *~ \#~ .\#* *.o *.log *.dvi *.toc core a.out