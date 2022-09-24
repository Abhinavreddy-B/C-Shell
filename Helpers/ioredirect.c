#include "../headers.h"
#include "../io_module/print_error.h"
#include "../commands/commands.h"
#include "./Helpers.h"


extern size_t MAX_NO_OF_PARTS;
extern size_t MAXIMUM_NO_OF_INNER_FILES;
extern int is_waiting_for_input;

void redirect(char* command[],int mode,int cnt){
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
    int infiledescr = -2;
    int outfiledescr = -2;
    char *command_split[MAX_NO_OF_PARTS];
    int command_split_cnt = 0;
    for(int i=0;i<cnt;i++){
        if(strcmp(command[i],"<") == 0){
            infiledescr = open(command[i+1],O_RDONLY);
            if(infiledescr == -1){
                char error[1000];
                sprintf(error,"%s: No such file or directory",command[i+1]);
                print_error(error);
                dup2(stdoutcpy,STDOUT_FILENO);
                dup2(stdincpy,STDIN_FILENO);
                return;
            }
            i++;
        }else if(strcmp(command[i],">") == 0){
            outfiledescr = open(command[i+1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(outfiledescr == -1){
                char error[1000];
                sprintf(error,"%s: No such file or directory",command[i+1]);
                print_error(error);
                dup2(stdoutcpy,STDOUT_FILENO);
                dup2(stdincpy,STDIN_FILENO);
                return;
            }
            i++;
        }else if(strcmp(command[i],">>") == 0){
            outfiledescr = open(command[i+1],O_WRONLY | O_APPEND | O_CREAT, 0644);
            if(outfiledescr == -1){
                char error[1000];
                sprintf(error,"%s: No such file or directory",command[i+1]);
                print_error(error);
                dup2(stdoutcpy,STDOUT_FILENO);
                dup2(stdincpy,STDIN_FILENO);
                return;
            }
            i++;
        }else if(strlen(command[i]) >=2 && command[i][0] == '<'){
            infiledescr = open(&command[i][1],O_RDONLY);
            if(infiledescr == -1){
                char error[1000];
                sprintf(error,"%s: No such file or directory",&command[i][1]);
                print_error(error);
                dup2(stdoutcpy,STDOUT_FILENO);
                dup2(stdincpy,STDIN_FILENO);
                return;
            }
        }else if(strlen(command[i]) >=2 && command[i][0] == '>' && command[i][1] != '>'){
            outfiledescr = open(&command[i][1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(outfiledescr == -1){
                char error[1000];
                sprintf(error,"%s: No such file or directory",&command[i][1]);
                print_error(error);
                dup2(stdoutcpy,STDOUT_FILENO);
                dup2(stdincpy,STDIN_FILENO);
                return;
            }
        }else if(strlen(command[i]) >=3 &&  command[i][0] == '>' && command[i][1] == '>'){
            outfiledescr = open(&command[i][2],O_WRONLY | O_APPEND | O_CREAT, 0644);
            if(outfiledescr == -1){
                char error[1000];
                sprintf(error,"%s: No such file or directory",&command[i][2]);
                print_error(error);
                dup2(stdoutcpy,STDOUT_FILENO);
                dup2(stdincpy,STDIN_FILENO);
                return;
            }
        }
        else{
            command_split[command_split_cnt] = command[i];
            command_split_cnt++;
        }
    }
    // printf("Here\n");
    if(infiledescr != -2){
        if(dup2(infiledescr,STDIN_FILENO) == -1){
            print_error("Some Problem in duplicating input file descr");
            perror("dup2 ");
            return;
        };
        close(infiledescr);
    }
    if(outfiledescr != -2){
        if(dup2(outfiledescr,STDOUT_FILENO) == -1){
            print_error("Some Problem in duplicating output file descr");
            perror("dup2 ");
            return;
        };
        close(outfiledescr);
    }
    splitter(command_split,mode,command_split_cnt);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
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
