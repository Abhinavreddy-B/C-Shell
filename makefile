flags = -pedantic -Wall -g

main: main.c getinfo.o prompt.o cd.o print_error.o command_helper.o
	gcc $(flags) main.c *.o -o main 

getinfo.o: getinfo.c print_error.o
	gcc $(flags) -c getinfo.c

prompt.o: prompt.c
	gcc $(flags) -c prompt.c

cd.o: cd.c print_error.o
	gcc $(flags) -c cd.c

print_error.o: print_error.c
	gcc $(flags) -c print_error.c

command_helper.o: cd.o print_error.o command_helper.c
	gcc $(flags) -c command_helper.c

clean:
	rm *.o