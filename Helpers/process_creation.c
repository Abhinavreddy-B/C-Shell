#include "../headers.h"
#include "../io_module/print_error.h"
#include "../io_module/prompt.h"
#include "../Linked_list/my_dll.h"
#include "../Linked_list/node.h"
#include "./Helpers.h"

#define INVALID_EXIT 2

extern char *username;
extern char *home_directory;
extern char *system_name;
extern char *time_taken;
extern char *relative_dir;
extern my_dll background_process_list;
extern int MAXIMUM_BACKGROUND_PROCESS_NAME;
extern time_t process_start_time;
extern int is_waiting_for_input;

void add_process_to_list(char* name,pid_t pid){
    ListElement_ptr new_process = (ListElement_ptr) malloc(sizeof(ListElement));
    new_process->name = (char *) malloc(MAXIMUM_BACKGROUND_PROCESS_NAME * sizeof(char));
    strcpy(new_process->name,name);
    new_process->pid = pid;
    new_process->index = return_last(&background_process_list) + 1;
    insert(&background_process_list , new_process);
}

void upon_child_exit(){
    int status;
    pid_t child_pid = waitpid(-1,&status,WNOHANG | WUNTRACED);
    if(child_pid == 0 || child_pid == -1){
        // nothing for now
    }else{
        printf("\n");
        ListElement_ptr found = Find_and_return(&background_process_list,child_pid);
        if(found == NULL){
            printf("Some problem\nabnormal interrupt\n");
            return;
        }else{
            printf("%s with pid = %d exited ", found->name ,found->pid);
            delete( &background_process_list , Find(&background_process_list,child_pid));
        }
        if(WIFEXITED(status)){
            printf("normally");
        }else if(WIFSIGNALED(status)){
            printf("Exited Abnomally");
            fflush(stdin);
            psignal(WTERMSIG(status),"Cause");
        }
        printf("\n");
        if(is_waiting_for_input){
            prompt(username, system_name, relative_dir, time_taken);
        }
        fflush(stdout);
    }
    return;
}

/**
 * @param mode is 0 => foreground , 1 => background
 */
int other_commands(char* command_split[],int cnt, int mode){
    pid_t pid = fork();
    if(pid == -1){
        print_error("Error creating child process");
        return 1;
    }
    if(pid == 0){
        command_split[cnt]=NULL;

        if(mode == 1){
            setpgid(0,0);
        }
        int ret_val = execvp(command_split[0],command_split);
        if(ret_val == -1){
            char error[500];
            sprintf(error,"%s: No such Builtin command or external executable",command_split[0]);
            print_error(error);
            perror("\033[31;1mError\033[0m");
            exit(INVALID_EXIT);
        }
    }else{
        if(mode == 0){
            time_t start = process_start_time;
            int wstatus;
            waitpid(pid,&wstatus,WSTOPPED | WSTOPPED);
            time_t run_time = time(NULL) - start;
            if(run_time >= 1){
                sprintf(time_taken,"|taken %lds",run_time);
            }else{
                time_taken[0]='\0';
            }
        }else{
            add_process_to_list(command_split[0],pid);
            printf("[%d] %d\n",return_last(&background_process_list),pid);
            signal(SIGCHLD,upon_child_exit);
            // return 1;
        }
        return 1;
    }
    return 1;
}