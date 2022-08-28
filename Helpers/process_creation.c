#include "../headers.h"
#include "../out_module/print_error.h"
#include "../out_module/prompt.h"
#include "../Linked_list/my_dll.h"
#include "../Linked_list/node.h"

extern char *username;
extern char *home_directory;
extern char system_name[];
extern char time_taken[];
extern char relative_dir[];
extern my_dll background_process_list;
extern int MAXIMUM_BACKGROUND_PROCESS_NAME;

void add_process_to_list(char* name,pid_t pid){
    ListElement_ptr new_process = (ListElement_ptr) malloc(sizeof(ListElement));
    new_process->name = (char *) malloc(MAXIMUM_BACKGROUND_PROCESS_NAME * sizeof(char));
    strcpy(new_process->name,name);
    // printf("%s\n",new_process->name);
    new_process->pid = pid;
    insert(&background_process_list , new_process);
}

void upon_child_exit(){
    int status;
    pid_t child_pid = waitpid(-1,&status,WNOHANG);
    if(child_pid == 0 || child_pid == -1){
        // nothing for now
    }else{
        printf("\n");
        ListElement_ptr found = Find_and_return(&background_process_list,child_pid);
        if(found == NULL){
            printf("Some problem\n");
        }else{
            printf("%s with pid = %d exited ", found->name ,found->pid);
            delete( &background_process_list , Find(&background_process_list,child_pid));
        }
        // printf("Something\n");
        if(WIFEXITED(status)){
            printf("normally");
            // printf("\033[32;1mPress Enter to Continue...\033[0m");
        }else if(WIFSIGNALED(status)){
            printf("Exited Abnomally");
            psignal(WTERMSIG(status),"Cause");
            // printf("\033[32;1mPress Enter to Continue...\033[0m");
        }
        printf("\n");
        prompt(username, system_name, relative_dir, time_taken);
        fflush(stdout);
    }
    return;
}

/**
 * @param mode is 0 => foreground , 1 => background
 */
int other_commands(char* command_split[],int cnt, int mode,char *time_taken){
    pid_t pid = fork();
    if(pid == -1){
        print_error("Error creating child process");
        return 1;
    }
    if(pid == 0){
        command_split[cnt]=NULL;
        int ret_val = execvp(command_split[0],command_split);
        if(ret_val == -1){
            print_error("No such Builtin command or external executable");
            perror("\033[31;1mError\033[0m");
            exit(1);
        }
    }else{
        if(mode == 0){
            // printf("Foreground Child started with %d\n",pid);
            time_t start = time(NULL);
            wait(NULL);
            time_t run_time = time(NULL) - start;
            if(run_time >= 1){
                // printf("Completed child process with %ld Seconds\n",run_time);
                sprintf(time_taken,"|taken %lds",run_time);
            }else{
                time_taken[0]='\0';
            }
            // printf("Foreground Child ended with %d\n",pid);
        }else{
            add_process_to_list(command_split[0],pid);
            printf("[%d] %d\n",get_size(background_process_list),pid);
            signal(SIGCHLD,upon_child_exit);
            // return 1;
        }
        return 1;
    }
    return 1;
}