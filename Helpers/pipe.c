#include "../headers.h"
#include "./Helpers.h"
#include "../io_module/print_error.h"

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
    if(stdincpy == -1){
        print_error("Some Problem in duplicating stdin - File: pipe.c");
        perror("dup ");
        return ;
    }
    int stdoutcpy = dup(STDOUT_FILENO);
    if(stdoutcpy == -1){
        print_error("Some Problem in duplicating stdout - File: pipe.c");
        perror("dup ");
        return;
    }
    int input_fd,output_fd;
    input_fd = dup(STDIN_FILENO);
    if(input_fd == -1){
        print_error("Some Problem in duplicating stdin - File: pipe.c");
        perror("dup ");
        return;
    }
    for(int i=0;i<cnt;i++){
        // close(STDOUT_FILENO);
        if(dup2(input_fd,STDIN_FILENO) == -1){
            print_error("Some Problem in duplicating input pipe - File: pipe.c");
            perror("dup2 ");
            return;
        };
        close(input_fd);
        if(i == cnt -1){
            output_fd = dup(stdoutcpy);
            if(output_fd == -1){
                print_error("Some Problem in restoring original stdout - File: pipe.c");
                perror("dup ");
                return;
            }
        }else{
            int pipe_fd[2];
            if(pipe(pipe_fd)==-1){
                print_error("Some Problem in creating a new pipe - File: pipe.c");
                perror("pipe ");
                return;
            };
            output_fd = pipe_fd[1];
            input_fd = pipe_fd[0];
        }
        if(dup2(output_fd,STDOUT_FILENO)==-1){
            print_error("Some Problem in redirecting to output pipe - File: pipe.c");
            perror("dup2 ");
            return;
        };
        close(output_fd);
        AndTokeniser(command_split[i]);
    }
    if(dup2(stdincpy,STDIN_FILENO)==-1){
        print_error("Some Problem in restoring original stdin - File: pipe.c");
        perror("dup2 ");
        return;
    };
    if(dup2(stdoutcpy,STDOUT_FILENO)==-1){
        print_error("Some Problem in restoring original stdout - File: pipe.c");
        perror("dup2 ");
        return;
    };
    close(stdincpy);
    close(stdoutcpy);
}