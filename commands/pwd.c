#include "../headers.h"
#include "./commands.h"

extern char *absolute_dir;

void present_working_directory(){
    printf("%s\n",absolute_dir);
}