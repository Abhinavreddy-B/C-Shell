#include "../headers.h"
#include "../Linked_list/node.h"
#include "../Linked_list/my_dll.h"
#include "../io_module/print_error.h"

extern my_dll background_process_list;

static int cmp(const void *a,const void *b){
    char * n1 = (*((ListElement_ptr *) a))->name;
    char * n2 = (*((ListElement_ptr *) b))->name;
    return strcmp(n1,n2);
}

void jobs(int running,int stopped){
    int size = get_size(background_process_list);
    ListElement_ptr bgs[size];
    nodeptr iter = background_process_list.root;
    for(int i=0;i<size;i++){
        bgs[i] = iter->data;
        iter = iter->next;
    }
    qsort(bgs,size,sizeof(bgs[0]),cmp);
    for(int i=0;i<size;i++){
        char pid_file[100];
        sprintf(pid_file,"/proc/%d/stat",bgs[i]->pid);
        FILE* pid_stat = fopen(pid_file,"r");
        char status;
        fscanf(pid_stat,"%*d %*s %c",&status);
        if(status != 'T'){
            if(running == 1){
                printf("[%d] Running %s [%d]\n",bgs[i]->index,bgs[i]->name,bgs[i]->pid);
            }
        }else if(stopped == 1){
            printf("[%d] Stopped %s [%d]\n",bgs[i]->index,bgs[i]->name,bgs[i]->pid);
        }
    }
}

void jobs_middleware(char *commands[],int cnt){
    int running=0,stopped=0; 
    for(int i=1;i<cnt;i++){
        if(commands[i][0] != '-'){
            char error[100];
            sprintf(error,"Unknown Argument: %s",commands[i]);
            print_error(error);
        }else if(strcmp(commands[i],"-r") == 0){
            running = 1;
        }else if(strcmp(commands[i],"-s") == 0){
            stopped = 1;
        }else{
            char error[100];
            sprintf(error,"Unsupported Flag: %s",commands[i]);
            print_error(error);
        }
    }
    if(running == 0 && stopped == 0){
        running = 1;
        stopped = 1;
    }
    jobs(running,stopped);
}