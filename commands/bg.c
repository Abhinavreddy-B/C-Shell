#include "../headers.h"
#include "../Linked_list/node.h"
#include "../Linked_list/my_dll.h"
#include "../io_module/print_error.h"

extern my_dll background_process_list;

void bg(pid_t pid){
    kill(pid,SIGCONT);
}

void bg_middleware(char* command[],int cnt){
    if(cnt != 2){
        print_error("Invalid No of arguments to fg");
        return;
    }
    long long int job_number = atoll(command[1]);
    if(job_number == 0){
        print_error("Invalid Job Number");
        return;
    }
    nodeptr iter = background_process_list.root;
    while(iter != NULL && iter->data->index != job_number){
        iter = iter->next;
    }
    if(iter == NULL){
        char error[100];
        sprintf(error,"No Job with Number %lld",job_number);
        print_error(error);
        return;
    }
    bg(iter->data->pid);
}