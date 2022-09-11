#include "../headers.h"
#include "../io_module/print_error.h"
#include "../commands/commands.h"
#include "./Helpers.h"


extern size_t MAX_NO_OF_PARTS;
extern size_t MAXIMUM_NO_OF_INNER_FILES;


/**
 * @param mode if 0 Foreground , 1 if background
*/
void splitter(char *command_split[],int mode,int cnt){
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
    }else if(strcmp(command_split[0],"jobs") == 0){
        jobs_middleware(command_split,cnt);
    }else if(strcmp(command_split[0],"sig") == 0){
        sig_middleware(command_split,cnt);
    }else if(strcmp(command_split[0],"fg") == 0){
        fg_middleware(command_split,cnt);
    }else if(strcmp(command_split[0],"bg") == 0){
        bg_middleware(command_split,cnt);
    }else{
        other_commands(command_split,cnt,mode);
    }
}

void redirect(char* command[],int mode,int cnt){
    int stdoutcpy = dup(STDOUT_FILENO);
    int stdincpy = dup(STDIN_FILENO);
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
        }else{
            command_split[command_split_cnt] = command[i];
            command_split_cnt++;
        }
    }
    // printf("Here\n");
    if(infiledescr != -2){
        dup2(infiledescr,STDIN_FILENO);
        close(infiledescr);
    }
    if(outfiledescr != -2){
        dup2(outfiledescr,STDOUT_FILENO);
        close(outfiledescr);
    }
    splitter(command_split,mode,command_split_cnt);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    dup2(stdincpy,STDIN_FILENO);
    dup2(stdoutcpy,STDOUT_FILENO);
    close(stdincpy);
    close(stdoutcpy);
}
