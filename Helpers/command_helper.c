#include "../headers.h"
#include "../commands/commands.h"
#include "../out_module/print_error.h"
#include "./Helpers.h"

extern size_t MAX_NO_OF_PARTS;
extern size_t MAXIMUM_NO_OF_INNER_FILES;
extern size_t MAXIMUM_INPUT_SIZE;

/**
 * @param mode if 0 Foreground , 1 if background
*/
void splitter(char *command, int mode)
{ 
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
            change_directory("~");
        }else if(cnt != 2){
            print_error("Invalid No Of arguments");
            return;
        }else{
            change_directory(command_split[1]);
        }
    }else if(strcmp(command_split[0],"pwd") == 0){
        if(cnt == 1){
            present_working_directory();
        }else{
            print_error("Invalid No Of arguments");
            return;
        }
    }else if(strcmp(command_split[0],"echo")==0){
        echo(command_split,cnt);
    }else if(strcmp(command_split[0],"ls") == 0){
        // printf("Hello\n");
        ls(command_split,cnt,MAXIMUM_NO_OF_INNER_FILES);
    }else{
        // int is_background_task = 0;
        // if(command_split[cnt-1][strlen(command_split[cnt-1])-1] == '&'){
            // command_split[cnt-1][strlen(command_split[cnt-1])-1] = '\0';
            // is_background_task = 1;
        // }
        other_commands(command_split,cnt,mode);
    }
}

void AndTokeniser(char *command_input){
    char command[MAXIMUM_INPUT_SIZE];
    strcpy(command,command_input);
    strcat(command," ");
    char* command_split[MAX_NO_OF_PARTS];
    char* part;
    int cnt=0;
    part =  command_split[cnt] = strtok (command,"&");
    while(part!=NULL){
        cnt++;
        part = command_split[cnt] = strtok (NULL, "&");
    }
    for(int i=0;i<cnt-1;i++){
        splitter(command_split[i],1);
    }
    splitter(command_split[cnt-1],0);
}

void shell_helper(char *input)
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
        // printf("Hello\n");
        AndTokeniser(split_input[i]);
    }
}