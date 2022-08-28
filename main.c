#include "out_module/prompt.h"
#include "headers.h"
#include "Helpers/command_helper.h"
#include "Helpers/getinfo.h"
#include "Linked_list/node.h"
#include "Linked_list/my_dll.h"

size_t MAXIMUM_DIRECTORY_LENGTH = 101LL;
size_t MAXIMUM_INPUT_SIZE = 101LL;
const size_t MAXIMUM_ERROR_LENGTH = 101LL;
const size_t MAXIMUM_SYSTEM_NAME = 101LL;
const size_t MAXIMUM_TIME_DIFFERENCE_SECONDS = 101LL;
int MAXIMUM_BACKGROUND_PROCESS_NAME = 101LL;
char *username;
char *home_directory = NULL;
char system_name[101LL];
char error_holder[101LL];
char time_taken[101LL];
char relative_dir[101LL];
char absolute_dir[101LL];
char prev_directory[101LL];
my_dll background_process_list;

int main()
{
    if (get_username(&username, error_holder) || get_systemname(system_name, error_holder) || get_home_dir(&home_directory, MAXIMUM_DIRECTORY_LENGTH, error_holder))
    {
        printf("%s\n", error_holder);
        _exit(1);
    }
    background_process_list = CreateList();
    relative_dir[0] = '~';
    relative_dir[1] = '\0';
    strcpy(absolute_dir, home_directory);
    prev_directory[0] = '\0';
    char input[MAXIMUM_INPUT_SIZE];
    while (1)
    {
        prompt(username, system_name, relative_dir, time_taken);
        input[0]='\0';
        scanf("%[^\n]s", input);
        getchar();
        if(input[0] != '\0'){
            shell_helper(input, MAXIMUM_DIRECTORY_LENGTH,
                  MAXIMUM_INPUT_SIZE, MAXIMUM_ERROR_LENGTH,
                  MAXIMUM_SYSTEM_NAME,username,
                  home_directory, error_holder,
                  relative_dir, absolute_dir,prev_directory,time_taken);
        }
        // printf("%.2s\n", &a[start]);
        // if (strncmp(&a[start], "cd ", 3) == 0)
        // {
        //     // printf("b1\n");
        //     change_directory(absolute_dir, relative_dir, &a[start + 3], home_directory,MAXIMUM_DIRECTORY_LENGTH);
        // }
    }
}
