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
extern const size_t MAX_NO_OF_PARTS;
extern const size_t MAXIMUM_INPUT_SIZE;


void add_process_to_list(char* name[],pid_t pid,int cnt){
    ListElement_ptr new_process = (ListElement_ptr) malloc(sizeof(ListElement));
    new_process->name = (char *) malloc(MAXIMUM_BACKGROUND_PROCESS_NAME * sizeof(char));
    new_process->name[0] = '\0';
    for(int i=0;i<cnt;i++){
        strcat(new_process->name,name[i]);
        strcat(new_process->name," ");
    }
    new_process->pid = pid;
    new_process->index = return_last(&background_process_list) + 1;
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
int other_commands(char* command_split_input[],int cnt, int mode){
    char* command_split[MAX_NO_OF_PARTS];
    for(int i=0;i<cnt;i++){
        command_split[i] = (char *) malloc(MAXIMUM_INPUT_SIZE * sizeof(char));
        if(command_split_input[i][0] == '~'){
            sprintf(command_split[i],"%s%s",home_directory,&command_split_input[i][1]);
        }else{
            strcpy(command_split[i],command_split_input[i]);
        }
    }
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
            // time_t start = process_start_time;
            int wstatus;
            
            waitpid(pid,&wstatus,WSTOPPED);
            // printf("Hello\n");
            if(WIFSTOPPED(wstatus)){
                add_process_to_list(command_split,pid,cnt);
                time_taken[0]='\0';
                return 1;
            }
            // if(WEXITSTATUS(wstatus) != EXIT_FAILURE){
                
            // }
        }else{
            add_process_to_list(command_split,pid,cnt);
            printf("[%d] %d\n",return_last(&background_process_list),pid);
            signal(SIGCHLD,upon_child_exit);
            // return 1;
        }
        return 1;
    }
    return 1;
}