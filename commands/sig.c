#include "../headers.h"
#include "../Linked_list/node.h"
#include "../Linked_list/my_dll.h"
#include "../io_module/print_error.h"

extern my_dll background_process_list;

void sig(int job_num,int signal_num){
    // int size = get_size(background_process_list);
    nodeptr iter = background_process_list.root;
    while(iter != NULL && iter->data->index != job_num){
        iter = iter->next;
    }
    if(iter == NULL){
        char error[100];
        sprintf(error,"No Job with Number %d",job_num);
        print_error(error);
        return;
    }
    kill(iter->data->pid,signal_num);
}

void sig_middleware(char* command[],int cnt){
    if(cnt != 3){
        print_error("Invalid number of parameters for sig");
        return;
    }
    long long int job_number = atoll(command[1]);
    long long int sig_number = atoll(command[2]);
    if(job_number == 0){
        print_error("Invalid Job Number");
        return;
    }
    if(sig_number == 0){
        print_error("Invalid Signal Number");
        return;
    }
    sig(job_number,sig_number);
}