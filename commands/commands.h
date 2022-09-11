#ifndef _COMMANDS_IMPLEMENTATON_H_
#define _COMMANDS_IMPLEMENTATON_H_
#include "../headers.h"

int change_directory(char *input);
void echo(char* input[],int cnt);
int ls(char* command[],int cnt,size_t MAXIMUM_NO_OF_INNER_PARTS);
void present_working_directory();
int discover_folder(char* command[],int cnt);
int get_history();
int pinfo_middleware(char* command[],int cnt);
void jobs_middleware(char *commands[],int cnt);
void sig_middleware(char* command[],int cnt);
void fg_middleware(char* command[],int cnt);
void bg_middleware(char* command[],int cnt);

#endif