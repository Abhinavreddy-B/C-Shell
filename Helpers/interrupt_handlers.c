#include "../headers.h"
#include "../io_module/prompt.h"
#include "./Helpers.h"

extern int is_waiting_for_input;
extern char *username;
extern char *home_directory;
extern char *system_name;
extern char *time_taken;
extern char *relative_dir;
extern char* input;

void CtrlDHandler(){
    printf("Exiting.....\n");
    exit(0);
}

void CtrlCHandler(){
    if(is_waiting_for_input){
        printf("\n");
        // input[0] = '\0';
        prompt(username, system_name, relative_dir, time_taken);
        fflush(stdout);
    }else{
        is_waiting_for_input = 1;
    }
    return;
}

void CtrlZHandler(){
    printf("Hello\n");
    if(is_waiting_for_input){
        printf("\n");
        prompt(username, system_name, relative_dir, time_taken);
        fflush(stdout);
    }else{
        is_waiting_for_input = 1;
    }
    return;
}