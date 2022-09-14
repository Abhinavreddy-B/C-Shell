#include "prompt.h"
#include "../headers.h"

extern char *username;
extern char *system_name;
extern char *time_taken;
extern char *relative_dir;
extern char *input;

void prompt() {
    printf("\r\033[0m<\033[0;32;1m%s\033[0m@\033[0;31;1m%s\033[0m:\033[34;1m%s%s>\033[0m %s",username, system_name, relative_dir ,time_taken,input);
}
