#include "../headers.h"
#include "../commands/cd.h"
#include "../commands/pwd.h"
#include "../commands/echo.h"
#include "../commands/ls.h"
#include "./process_creation.h"
#include "../out_module/print_error.h"

void splitter(char *command, size_t MAXIMUM_DIRECTORY_LENGTH,
              size_t MAXIMUM_INPUT_SIZE, const size_t MAXIMUM_ERROR_LENGTH,
              const size_t MAXIMUM_SYSTEM_NAME, char *username,
              char *home_directory, char *error_holder,
              char *relative_dir, char *absolute_dir, char* prev_directory, char* time_taken)
{
    size_t MAX_NO_OF_PARTS = 101LL;
    size_t MAXIMUM_NO_OF_INNER_FILES = 101LL;
    // printf("%s\n",command);
    char* command_split[MAX_NO_OF_PARTS];
    char* part;
    int cnt=0;
    part =  command_split[cnt] = strtok (command," \t");
    while(part!=NULL){
        cnt++;
        part = command_split[cnt] = strtok (NULL, " \t");
    }
    if(cnt == 0){
        return;
    }
    if(strcmp(command_split[0],"cd") == 0){
        if(cnt == 1){
            change_directory(absolute_dir,relative_dir,"~",home_directory, prev_directory ,MAXIMUM_DIRECTORY_LENGTH);
        }else if(cnt != 2){
            print_error("Invalid No Of arguments");
            return;
        }else{
            change_directory(absolute_dir,relative_dir,command_split[1],home_directory, prev_directory ,MAXIMUM_DIRECTORY_LENGTH);
        }
    }else if(strcmp(command_split[0],"pwd") == 0){
        if(cnt == 1){
            present_working_directory(absolute_dir);
        }else{
            print_error("Invalid No Of arguments");
            return;
        }
    }else if(strcmp(command_split[0],"echo")==0){
        echo(command_split,cnt);
    }else if(strcmp(command_split[0],"ls") == 0){
        ls(command_split,cnt,MAXIMUM_NO_OF_INNER_FILES);
    }else{
        int is_background_task = 0;
        if(command_split[cnt-1][strlen(command_split[cnt-1])-1] == '&'){
            command_split[cnt-1][strlen(command_split[cnt-1])-1] = '\0';
            is_background_task = 1;
        }
        other_commands(command_split,cnt,is_background_task,time_taken);
    }
}

void shell_helper(char *input, size_t MAXIMUM_DIRECTORY_LENGTH,
                  size_t MAXIMUM_INPUT_SIZE, const size_t MAXIMUM_ERROR_LENGTH,
                  const size_t MAXIMUM_SYSTEM_NAME, char *username,
                  char *home_directory, char *error_holder,
                  char *relative_dir, char *absolute_dir, char* prev_directory, char* time_taken)
{
    // char input_temp[MAXIMUM_INPUT_SIZE];
    // remove_unnecessary(input,input_temp);
    size_t MAXIMUM_NO_OF_TOKENS = 101LL ;
    char* split_input[MAXIMUM_NO_OF_TOKENS];
    // printf("%s\n",input);
    char* token;
    int tokencnt=0;
    token = split_input[tokencnt] =strtok(input,";");
    while(token != NULL){
        tokencnt++;
        token = split_input[tokencnt] = strtok(NULL,";");
    }
    for(int i=0;i<tokencnt;i++){
        // printf ("%s\n",split_input[i]);
        splitter(split_input[i], MAXIMUM_DIRECTORY_LENGTH,
                  MAXIMUM_INPUT_SIZE, MAXIMUM_ERROR_LENGTH,
                  MAXIMUM_SYSTEM_NAME,username,
                  home_directory, error_holder,
                  relative_dir, absolute_dir,prev_directory, time_taken);
    }
}