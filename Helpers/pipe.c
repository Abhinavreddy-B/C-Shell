#include "../headers.h"
#include "./Helpers.h"

extern size_t MAX_NO_OF_PARTS;
extern size_t MAXIMUM_NO_OF_INNER_FILES;
extern size_t MAXIMUM_INPUT_SIZE;

void piper(char* command){
    char* command_split[MAX_NO_OF_PARTS];
    char* part;
    int cnt=0;
    part =  command_split[cnt] = strtok (command,"|");
    while(part!=NULL){
        cnt++;
        part = command_split[cnt] = strtok (NULL, "|");
    }
    int stdincpy = dup(STDIN_FILENO);
    int stdoutcpy = dup(STDOUT_FILENO);
    int input_fd,output_fd;
    input_fd = dup(STDIN_FILENO);
    for(int i=0;i<cnt;i++){
        // close(STDOUT_FILENO);
        dup2(input_fd,STDIN_FILENO);
        close(input_fd);
        if(i == cnt -1){
            output_fd = dup(stdoutcpy);
        }else{
            int pipe_fd[2];
            pipe(pipe_fd);
            output_fd = pipe_fd[1];
            input_fd = pipe_fd[0];
        }
        dup2(output_fd,STDOUT_FILENO);
        close(output_fd);
        AndTokeniser(command_split[i]);
    }
    dup2(stdincpy,STDIN_FILENO);
    dup2(stdoutcpy,STDOUT_FILENO);
    close(stdincpy);
    close(stdoutcpy);
}