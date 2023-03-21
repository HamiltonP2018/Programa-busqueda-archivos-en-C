all: main.o  buscar.o
	gcc -o buscar main.o buscar.o

main.o: main.c
	gcc -c -o main.o main.c

buscar.o: buscar.c buscar.h
	gcc -c -o buscar.o buscar.c

clean:
	rm -rf *.o buscar