#include "out_module/prompt.h"
#include "out_module/print_error.h"
#include "headers.h"
#include "Helpers/Helpers.h"
#include "Linked_list/node.h"
#include "Linked_list/my_dll.h"

size_t MAXIMUM_DIRECTORY_LENGTH = 101LL;
size_t MAXIMUM_INNER_DIRECTORIES = 101LL;
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
char** history;
char * history_file_path;
int no_of_commands_in_history;

int main()
{
    printf("\033[33m******************************************************\n");
    printf("*                    Custom shell                    *\n");
    printf("*                Abhinav Reddy Boddu                 *\n");
    printf("*                     2021101034                     *\n");
    printf("******************************************************\n\033[0m");
    history = (char **) malloc(20*sizeof(char *));
    for(int i=0;i<20;i++){
        history[i] = (char *) malloc(MAXIMUM_INPUT_SIZE * sizeof(char));
    }
    system_name = (char *) malloc((MAXIMUM_SYSTEM_NAME)*sizeof(char));
    time_taken = (char *) malloc((MAXIMUM_TIME_DIFFERENCE_SECONDS)*sizeof(char));
    relative_dir = (char *) malloc((MAXIMUM_DIRECTORY_LENGTH)*sizeof(char));
    absolute_dir = (char *) malloc((MAXIMUM_DIRECTORY_LENGTH)*sizeof(char));
    prev_directory = (char *) malloc((MAXIMUM_DIRECTORY_LENGTH)*sizeof(char));
    history_file_path = (char *) malloc(MAXIMUM_DIRECTORY_LENGTH * sizeof(char));
    background_process_list = CreateList();
    relative_dir[0] = '~';
    relative_dir[1] = '\0';
    // printf("Hello\n");
    prev_directory[0] = '\0';
    char input[MAXIMUM_INPUT_SIZE];
    char previous_input[MAXIMUM_INPUT_SIZE];
    previous_input[0] = '\0';
    // printf("Hello\n");
    // printf("Hello\n");
    if (get_username(&username, error_holder) || get_systemname(system_name, error_holder) || get_home_dir(&home_directory, MAXIMUM_DIRECTORY_LENGTH, error_holder))
    {
        printf("%s\n", error_holder);
        _exit(1);
    }
    strcpy(absolute_dir, home_directory);
    sprintf(history_file_path,"%s/.shell_history.tmp",home_directory);
    FILE* history_file = fopen(history_file_path,"r");
    if(history_file != NULL){
        no_of_commands_in_history = load_to_history(history_file,history);
        fclose(history_file);
    }
    while (1)
    {
        prompt(username, system_name, relative_dir, time_taken);
        input[0]='\0';
        strcpy(previous_input,input);
        scanf("%[^\n]s", input);
        getchar();
        process_start_time = time(NULL);
        if(input[0] != '\0'){
            if(strcmp(input,previous_input) != 0){
                history_file = fopen(history_file_path,"w");
                add_to_history(input,history,history_file,&no_of_commands_in_history);
                fclose(history_file);
            }
            if(check_if_valid_syntax(input) == -1){
                print_error("syntax error");
            }else{
                shell_helper(input);
            }
        }
    }
}
