#include "../headers.h"
#include "../commands/commands.h"
#include "../io_module/print_error.h"
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
        // if(!is_last){
            // print_error("Invalid Command, syntax error");
        // }
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
        present_working_directory();
    }else if(strcmp(command_split[0],"echo")==0){
        echo(command_split,cnt);
    }else if(strcmp(command_split[0],"ls") == 0){
        // printf("Hello\n");
        ls(command_split,cnt,MAXIMUM_NO_OF_INNER_FILES);
    }else if(strcmp(command_split[0],"discover") == 0){
        discover_folder(command_split,cnt);
    }else if(strcmp(command_split[0],"history") == 0){
        get_history();
    }else if(strcmp(command_split[0],"pinfo") == 0){
        pinfo_middleware(command_split,cnt);
    }
    else{
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
    if(strstr(command_input,"&&") != NULL){
        print_error("Invalid Command, syntax error");
        return;
    }
    // strcpy(command,command_input);
    // strcat(command," ");
    sprintf(command," %s ",command_input);
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
    // command_split[cnt-1][strlen(command_split[cnt-1])-1] = '\0';
    if(strlen(command_split[cnt-1])!=1){
        splitter(command_split[cnt-1],0);
    }
        
}

void shell_helper(char *input)
{
    // strcat(input," ");
    char modified_input[MAXIMUM_INPUT_SIZE];
    sprintf(modified_input," %s ",input);
    size_t MAXIMUM_NO_OF_TOKENS = 101LL ;
    char* split_input[MAXIMUM_NO_OF_TOKENS];
    char* token;
    int tokencnt=0;
    token = split_input[tokencnt] =strtok(modified_input,";");
    while(token != NULL){
        tokencnt++;
        token = split_input[tokencnt] = strtok(NULL,";");
    }
    if(tokencnt == 0){
        print_error("Invalid Command, syntax error");
        return;
    }
    for(int i=0;i<tokencnt;i++){;
        // printf ("%s\n",split_input[i]);
        // printf("Hello\n");
        AndTokeniser(split_input[i]);
    }
}