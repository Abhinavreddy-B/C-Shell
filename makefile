flags = -pedantic -Wall -g

main: main.c getinfo.o prompt.o cd.o print_error.o command_helper.o pwd.o echo.o ls.o process_creation.o my_dll.o node.o
	gcc $(flags) main.c *.o -o main 

getinfo.o: ./Helpers/getinfo.c
	gcc $(flags) -c ./Helpers/getinfo.c

prompt.o: ./out_module/prompt.c
	gcc $(flags) -c ./out_module/prompt.c

cd.o: ./commands/cd.c
	gcc $(flags) -c ./commands/cd.c

print_error.o: ./out_module/print_error.c
	gcc $(flags) -c ./out_module/print_error.c

command_helper.o: ./Helpers/command_helper.c
	gcc $(flags) -c ./Helpers/command_helper.c

pwd.o: ./commands/pwd.c
	gcc $(flags) -c ./commands/pwd.c

echo.o: ./commands/echo.c
	gcc $(flags) -c ./commands/echo.c

ls.o: ./commands/ls.c
	gcc $(flags) -c ./commands/ls.c

process_creation.o: ./Helpers/process_creation.c
	gcc $(flags) -c ./Helpers/process_creation.c

my_dll.o: ./Linked_list/my_dll.h ./Linked_list/my_dll.c
	gcc $(flags) -c ./Linked_list/my_dll.c

node.o: ./Linked_list/node.h ./Linked_list/node.c
	gcc $(flags) -c ./Linked_list/node.c

clean:
	rm *.o main