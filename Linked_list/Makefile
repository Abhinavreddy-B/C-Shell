compargs = gcc -g3 -Wall -pedantic

main: main.c my_dll.h my_dll.o
	$(compargs) node.o my_dll.o main.c -o main

my_dll.o: my_dll.h my_dll.c node.o node.h
	$(compargs) -c my_dll.c > my_dll.o

node.o: node.h node.c
	$(compargs) -c node.c > node.o