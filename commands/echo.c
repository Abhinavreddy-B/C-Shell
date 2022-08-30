#include "../headers.h"
#include "./commands.h"

void echo(char* input[],int cnt){
    if(cnt==1){
        printf("\n");
        return;
    }
    for(int i=1;i<cnt-1;i++){
        printf("%s ",input[i]);
    }
    printf("%s\n",input[cnt-1]);
}