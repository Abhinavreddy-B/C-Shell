#include "prompt.h"
#include "headers.h"

void prompt(const char* const username, const char* const systemname, const char* const directory) {
    printf("\033[0;32m<%s@%s:%s>\033[m ",username, systemname, directory);    
}
