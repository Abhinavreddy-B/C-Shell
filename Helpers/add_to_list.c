#include "../Linked_list/my_dll.h"
#include "../Linked_list/node.h"
#include "../headers.h"

extern my_dll background_process_list;
extern int MAXIMUM_BACKGROUND_PROCESS_NAME;

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
