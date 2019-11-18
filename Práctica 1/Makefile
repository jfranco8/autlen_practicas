CC = gcc
CFLAGS = -g
OBJ = *.o

all: pr_afnd

pr_afnd: pr_afnd.o transforma.o afnd.o
	$(CC) $(CFLAGS) -o pr_afnd pr_afnd.o transforma.o afnd.o

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGS) -c transforma.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS) -c afnd.c

clean:
	rm -rf pr_afnd $(OBJ) *.dot
