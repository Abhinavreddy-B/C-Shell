#include "prompt.h"
#include "../headers.h"

void prompt(const char* const username, const char* const systemname, const char* const directory, char* time_taken) {
    printf("\033[0m<\033[0;32;1m%s\033[0m@\033[0;31;1m%s\033[0m:\033[34;1m%s%s>\033[0m ",username, systemname, directory,time_taken);
    time_taken[0] = '\0';
}
