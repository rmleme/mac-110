#
# Makefile para trabalhar com ep2 (com PostScript).
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

OBJS = gb_flip.o grafo_aleat.o ep2.o

#======================================================================

gb_flip.o: gb_flip.h gb_flip.c
	$(CC) $(CFLAGS) -c $*.c

grafo_aleat.o: gb_flip.h gb_flip.c grafo_aleat.h grafo_aleat.c
	$(CC) $(CFLAGS) -c $*.c

ep2.o: ep2.c grafo_aleat.h grafo_aleat.c
	$(CC) $(CFLAGS) -c $*.c

ep2: $(OBJS)
	$(CC) $(LDFLAGS) -o ep2 $(OBJS) $(LDLIBS) 

clean:
	$(RM) *~ \#~ .\#* *.o *.log *.dvi *.toc core a.out

