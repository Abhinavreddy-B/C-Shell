#ifndef _GET_INFORMATION_H_

#include "../headers.h"
#define _GET_INFORMATION_H_

int get_username(char** username_ptr,char errors[]);
int get_systemname(char* system_name,char errors[]);
int get_home_dir(char** home_directory_ptr,size_t MAXIMUM_DIRECTORY_LENGTH,char errors[]);

#endif