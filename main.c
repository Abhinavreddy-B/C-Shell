#include "out_module/prompt.h"
#include "headers.h"
#include "Helpers/command_helper.h"
#include "Helpers/getinfo.h"

int main()
{
    size_t MAXIMUM_DIRECTORY_LENGTH = 101LL;
    size_t MAXIMUM_INPUT_SIZE = 101LL;
    const size_t MAXIMUM_ERROR_LENGTH = 101LL;
    const size_t MAXIMUM_SYSTEM_NAME = 101LL;
    char *username;
    char *home_directory = NULL;
    char system_name[MAXIMUM_SYSTEM_NAME];
    char error_holder[MAXIMUM_ERROR_LENGTH];
    if (get_username(&username, error_holder) || get_systemname(system_name, error_holder) || get_home_dir(&home_directory, MAXIMUM_DIRECTORY_LENGTH, error_holder))
    {
        printf("%s\n", error_holder);
        _exit(1);
    }
    char relative_dir[MAXIMUM_DIRECTORY_LENGTH];
    relative_dir[0] = '~';
    relative_dir[1] = '\0';
    char absolute_dir[MAXIMUM_DIRECTORY_LENGTH];
    char prev_directory[MAXIMUM_DIRECTORY_LENGTH];
    strcpy(absolute_dir, home_directory);
    strcpy(prev_directory, home_directory);
    while (1)
    {
        prompt(username, system_name, relative_dir);
        char input[MAXIMUM_INPUT_SIZE];
        scanf("%[^\n]s", input);
        getchar();
        if(input[0] != '\0'){
            shell_helper(input, MAXIMUM_DIRECTORY_LENGTH,
                  MAXIMUM_INPUT_SIZE, MAXIMUM_ERROR_LENGTH,
                  MAXIMUM_SYSTEM_NAME,username,
                  home_directory, error_holder,
                  relative_dir, absolute_dir,prev_directory);
        }
        // printf("%.2s\n", &a[start]);
        // if (strncmp(&a[start], "cd ", 3) == 0)
        // {
        //     // printf("b1\n");
        //     change_directory(absolute_dir, relative_dir, &a[start + 3], home_directory,MAXIMUM_DIRECTORY_LENGTH);
        // }
    }
}
