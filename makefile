flags = -pedantic -Wall -g

main: main.c getinfo.o prompt.o cd.o print_error.o command_helper.o pwd.o echo.o
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

clean:
	rm *.o