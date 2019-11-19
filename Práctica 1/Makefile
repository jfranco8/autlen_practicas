CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CCFLAGS = -g
OBJ = *.o

all: pr_afnd prueba3

pr_afnd: pr_afnd.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o pr_afnd pr_afnd.o transforma.o afnd.o intermedia.o

prueba3: prueba3.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o prueba3 prueba3.o transforma.o afnd.o intermedia.o

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGS) -c transforma.c

intermedia.o: intermedia.c intermedia.h
	$(CC) $(CFLAGS) -c intermedia.c

afnd.o: afnd.c afnd.h
	$(CC) $(CCFLAGS) -c afnd.c

clean:
	rm -rf pr_afnd prueba3 $(OBJ) *.dot
