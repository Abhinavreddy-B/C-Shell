#include "../headers.h"

extern char** history;
extern int no_of_commands_in_history;

int get_history(){
    // printf("%d\n",no_of_commands_in_history);
    if(no_of_commands_in_history <= 10){
        for(int i=0;i<no_of_commands_in_history;i++){
            printf("%s\n",history[i]);
        }
    }else{
        for(int i=no_of_commands_in_history-10;i<no_of_commands_in_history;i++){
            printf("%s\n",history[i]);
        }
    }
    return 0;
}