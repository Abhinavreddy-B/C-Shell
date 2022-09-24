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
void spaceTokenise(char *command, int mode)
{ 
    char* command_split[MAX_NO_OF_PARTS];
    char* part;
    int cnt=0;
    part =  command_split[cnt] = strtok (command," \t");
    while(part!=NULL){
        cnt++;
        part = command_split[cnt] = strtok (NULL, " \t");
    }
    redirect(command_split,mode,cnt);
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
        spaceTokenise(command_split[i],1);
    }
    // command_split[cnt-1][strlen(command_split[cnt-1])-1] = '\0';
    if(strlen(command_split[cnt-1])!=1){
        spaceTokenise(command_split[cnt-1],0);
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
    for(int i=0;i<tokencnt;i++){
        piper(split_input[i]);
    }
}