#include "../headers.h"
#include "commands.h"
#include "../io_module/print_error.h"

extern char *home_directory;
// cat /proc/0/status
// void read_garbage(char garbage[],FILE* input,int cnt){
//     for(int i=0;i<cnt;i++){
//         getline(garbage,1000,input);
//     }
// }

int pinfo(pid_t pid){
    char pinfo_filepath[30];
    sprintf(pinfo_filepath,"/proc/%d/stat",pid);
    FILE* pinfo_file = fopen(pinfo_filepath,"r");
    char executable_path[1000];
    char status;
    unsigned long virtual_memory;
    pid_t pgrp;
    pid_t tpgid;
    fscanf(pinfo_file,"%*d%*s %c %*d%d%*d%*d%d%*u%*u%*u%*u%*u%*u%*u%*d%*d%*d%*d%*d%*d%*u%lu",&status,&pgrp,&tpgid,&virtual_memory);

    fclose(pinfo_file);
    sprintf(pinfo_filepath,"/proc/%d/exe",pid);
    int no_of_chars_read = readlink(pinfo_filepath,executable_path,1000);
    executable_path[no_of_chars_read] = '\0';
    printf("pid : %d\n",pid);
    if(pgrp == tpgid){
        printf("process status : %c+\n",status);
    }else{
        printf("process status : %c\n",status);
    }
    printf("memory : %lu\n",virtual_memory);
    if(strncmp(executable_path,home_directory,strlen(home_directory)) == 0){
        printf("executable path : ~%s\n",&executable_path[strlen(home_directory)]);
    }else{
        printf("executable path : %s\n",executable_path);
    }
    return 0;
}

int pinfo_middleware(char* command[],int cnt){
    if(cnt > 2){
        print_error("Invalid no of arguments for \"pinfo\"");
    }
    pid_t pid;
    if(cnt == 1){
        pid = getpid();
    }else{
        sscanf(command[1],"%d",&pid);
    }
    pinfo(pid);
    return 0;
}