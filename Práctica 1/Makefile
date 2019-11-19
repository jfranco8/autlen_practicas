CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
OBJ = *.o

all: pr_afnd

pr_afnd: pr_afnd.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o pr_afnd pr_afnd.o transforma.o afnd.o intermedia.o

transforma.o: transforma.c transforma.h 
	$(CC) $(CFLAGS) -c transforma.c

intermedia.o: intermedia.c intermedia.h
	$(CC) $(CFLAGS) -c intermedia.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS) -c afnd.c

clean:
	rm -rf pr_afnd $(OBJ) *.dot
