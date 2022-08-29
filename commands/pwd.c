#include "../headers.h"
#include "./pwd.h"

extern char *absolute_dir;

void present_working_directory(){
    printf("%s\n",absolute_dir);
}