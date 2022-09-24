#include "../headers.h"
#include "../io_module/print_error.h"
#include "../commands/commands.h"
#include "./Helpers.h"


extern size_t MAX_NO_OF_PARTS;
extern size_t MAXIMUM_NO_OF_INNER_FILES;
extern int is_waiting_for_input;

/**
 * @param mode if 0 Foreground , 1 if background
*/
void splitter(char *command_split[],int mode,int cnt){
    if(cnt == 0 || is_waiting_for_input){
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