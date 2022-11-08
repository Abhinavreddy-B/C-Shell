#include "../headers.h"
#include "../io_module/prompt.h"
#include "./Helpers.h"
#include "../Linked_list/my_dll.h"
#include "../Linked_list/node.h"

extern int is_waiting_for_input;
extern char *username;
extern char *home_directory;
extern char *system_name;
extern char *time_taken;
extern char *relative_dir;
extern char* input;
extern my_dll background_process_list;
extern int MAXIMUM_BACKGROUND_PROCESS_NAME;

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
            int cnt=0;
            while(found->name[cnt] != '\0' && found->name[cnt] != ' '){
                cnt++;
            };
            found->name[cnt]='\0';
            printf("%s with pid = %d exited ", found->name ,found->pid);
            delete( &background_process_list , Find(&background_process_list,child_pid));
        }
        if(WIFEXITED(status)){
            printf("normally");
        }else if(WIFSIGNALED(status)){
            printf("Exited Abnomally");
            fflush(stdout);
            // psignal(WTERMSIG(status),"Cause");
        }
        printf("\n");
        if(is_waiting_for_input){
            prompt(username, system_name, relative_dir, time_taken);
        }
        fflush(stdout);
    }
    return;
}

void CtrlDHandler(){
    printf("Exiting.....\n");
    exit(0);
}

void CtrlCHandler(){
    if(is_waiting_for_input){
        printf("^C\n");
        // input[0] = '\0';
        prompt(username, system_name, relative_dir, time_taken);
        fflush(stdout);
    }else{
        is_waiting_for_input = 1;
        printf("\n");
    }
    return;
}

void CtrlZHandler(){
    if(is_waiting_for_input){
        printf("^Z\n");
        prompt(username, system_name, relative_dir, time_taken);
        fflush(stdout);
    }else{
        is_waiting_for_input = 1;
        setpgid(0,0);
        printf("\n");
    }
    return;
}