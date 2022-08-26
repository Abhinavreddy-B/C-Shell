#ifndef _SHELL_HELPER_H_
#include "../headers.h"
#define _SHELL_HELPER_H_

void shell_helper(char *input, size_t MAXIMUM_DIRECTORY_LENGTH,
                  size_t MAXIMUM_INPUT_SIZE, const size_t MAXIMUM_ERROR_LENGTH,
                  const size_t MAXIMUM_SYSTEM_NAME, char *username,
                  char *home_directory, char *error_holder,
                  char *relative_dir, char *absolute_dir, char* old_directory);

#endif