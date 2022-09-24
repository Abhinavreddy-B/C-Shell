flags = -pedantic -Wall -g

main: main.c input.o getinfo.o splitter.o add_to_list.o interrupt_handlers.o pipe.o fg.o bg.o sig.o prompt.o History.o jobs.o check_invalid.o cd.o print_error.o tokenize.o pinfo.o pwd.o echo.o ls.o process_creation.o my_dll.o node.o discover.o History.o history.o ioredirect.o
	gcc $(flags) main.c *.o -o main
	make clean

add_to_list.o: ./Helpers/add_to_list.c
	gcc $(flags) -c ./Helpers/add_to_list.c

splitter.o: ./Helpers/splitter.c
	gcc $(flags) -c ./Helpers/splitter.c

getinfo.o: ./Helpers/getinfo.c
	gcc $(flags) -c ./Helpers/getinfo.c

input.o: ./io_module/input.c
	gcc $(flags) -c ./io_module/input.c

History.o: ./Helpers/History.c
	gcc $(flags) -c ./Helpers/History.c

interrupt_handlers.o: ./Helpers/interrupt_handlers.c
	gcc $(flags) -c ./Helpers/interrupt_handlers.c

prompt.o: ./io_module/prompt.c
	gcc $(flags) -c ./io_module/prompt.c

cd.o: ./commands/cd.c
	gcc $(flags) -c ./commands/cd.c

fg.o: ./commands/fg.c
	gcc $(flags) -c ./commands/fg.c

bg.o: ./commands/bg.c
	gcc $(flags) -c ./commands/bg.c

jobs.o: ./commands/jobs.c
	gcc $(flags) -c ./commands/jobs.c

history.o: ./commands/history.c
	gcc $(flags) -c ./commands/history.c

check_invalid.o: ./Helpers/check_invalid.c
	gcc $(flags) -c ./Helpers/check_invalid.c

print_error.o: ./io_module/print_error.c
	gcc $(flags) -c ./io_module/print_error.c

tokenize.o: ./Helpers/tokenize.c
	gcc $(flags) -c ./Helpers/tokenize.c

pwd.o: ./commands/pwd.c
	gcc $(flags) -c ./commands/pwd.c

echo.o: ./commands/echo.c
	gcc $(flags) -c ./commands/echo.c

sig.o: ./commands/sig.c
	gcc $(flags) -c ./commands/sig.c

ls.o: ./commands/ls.c
	gcc $(flags) -c ./commands/ls.c

discover.o: ./commands/discover.c
	gcc $(flags) -c ./commands/discover.c

pinfo.o: ./commands/pinfo.c
	gcc $(flags) -c ./commands/pinfo.c

process_creation.o: ./Helpers/process_creation.c
	gcc $(flags) -c ./Helpers/process_creation.c

ioredirect.o: ./Helpers/ioredirect.c
	gcc $(flags) -c ./Helpers/ioredirect.c

pipe.o: ./Helpers/pipe.c
	gcc $(flags) -c ./Helpers/pipe.c

my_dll.o: ./Linked_list/my_dll.h ./Linked_list/my_dll.c
	gcc $(flags) -c ./Linked_list/my_dll.c

node.o: ./Linked_list/node.h ./Linked_list/node.c
	gcc $(flags) -c ./Linked_list/node.c

clean:
	rm *.o