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
size_t MAX_NO_OF_PARTS = 101LL;
size_t MAXIMUM_NO_OF_INNER_FILES = 101LL;
char *username;
char *home_directory = NULL;
char *system_name;
char error_holder[101LL];
char *time_taken;
char *relative_dir;
char *absolute_dir;
char *prev_directory;
my_dll background_process_list;
time_t process_start_time;

int main()
{
    system_name = (char *) malloc((MAXIMUM_SYSTEM_NAME)*sizeof(char));
    time_taken = (char *) malloc((MAXIMUM_TIME_DIFFERENCE_SECONDS)*sizeof(char));
    relative_dir = (char *) malloc((MAXIMUM_DIRECTORY_LENGTH)*sizeof(char));
    absolute_dir = (char *) malloc((MAXIMUM_DIRECTORY_LENGTH)*sizeof(char));
    prev_directory = (char *) malloc((MAXIMUM_DIRECTORY_LENGTH)*sizeof(char));
    background_process_list = CreateList();
    relative_dir[0] = '~';
    relative_dir[1] = '\0';
    // printf("Hello\n");
    prev_directory[0] = '\0';
    char input[MAXIMUM_INPUT_SIZE];
    if (get_username(&username, error_holder) || get_systemname(system_name, error_holder) || get_home_dir(&home_directory, MAXIMUM_DIRECTORY_LENGTH, error_holder))
    {
        printf("%s\n", error_holder);
        _exit(1);
    }
    strcpy(absolute_dir, home_directory);
    while (1)
    {
        prompt(username, system_name, relative_dir, time_taken);
        input[0]='\0';
        scanf("%[^\n]s", input);
        getchar();
        process_start_time = time(NULL);
        if(input[0] != '\0'){
            shell_helper(input);
        }
        // printf("%.2s\n", &a[start]);
        // if (strncmp(&a[start], "cd ", 3) == 0)
        // {
        //     // printf("b1\n");
        //     change_directory(absolute_dir, relative_dir, &a[start + 3], home_directory,MAXIMUM_DIRECTORY_LENGTH);
        // }
    }
}
