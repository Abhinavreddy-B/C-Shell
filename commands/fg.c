#include "../headers.h"
#include "../Linked_list/node.h"
#include "../Linked_list/my_dll.h"
#include "../io_module/print_error.h"

extern my_dll background_process_list;

void fg(pid_t pid){
    // printf("%d - %d\n",pid,getpgrp());
    // setpgid(pid,getpgid(0));
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);

    int temp = getpgrp();
    tcsetpgrp(STDIN_FILENO,pid);
    kill(pid,SIGCONT);
    waitpid(pid,NULL,WSTOPPED | WUNTRACED);
    tcsetpgrp(STDIN_FILENO,temp);

    signal(SIGTTIN,SIG_DFL);
    signal(SIGTTOU,SIG_DFL);
}

void fg_middleware(char* command[],int cnt){
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
    fg(iter->data->pid);
    delete(&background_process_list,Find(&background_process_list,iter->data->pid));
}