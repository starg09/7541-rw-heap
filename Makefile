CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
EXEC=correr_pruebas
OBJ=testing.o heap.o 
CC=gcc

all: $(EXEC)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clear:
	rm $(OBJ) $(EXEC)

$(EXEC): $(OBJ) prueba_heap.c main.c
	$(CC) $(CFLAGS) $(OBJ) prueba_heap.c main.c -o $(EXEC)

zip: %.c %.h Makefile
	rm ./Heap\ -\ 98373\ -\ Bianchi\ -\ 96251\ -\ Queirolo\ Dominguez.zip
	zip ./Heap\ -\ 98373\ -\ Bianchi\ -\ 96251\ -\ Queirolo\ Dominguez.zip *.c *.h Makefile