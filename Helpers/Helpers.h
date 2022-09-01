#ifndef _HELPER_FUNCTION_H_
#define _HELPER_FUNCTION_H_
#include "../headers.h"

void shell_helper(char *input);
int get_username(char** username_ptr,char errors[]);
int get_systemname(char* system_name,char errors[]);
int get_home_dir(char** home_directory_ptr,size_t MAXIMUM_DIRECTORY_LENGTH,char errors[]);
int other_commands(char* command_split[],int cnt, int mode);
int load_to_history(FILE* input, char* history[20]);
void add_to_history(char *command, char* history[20],FILE* output,int* no_of_existing_history);
int check_if_valid_syntax(char * input);

#endif