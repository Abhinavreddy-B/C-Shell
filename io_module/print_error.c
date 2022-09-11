#include "../headers.h"
#include "print_error.h"

void print_error(char *err){
    fprintf(stderr,"\033[1;31m%s\n\033[m",err);
}