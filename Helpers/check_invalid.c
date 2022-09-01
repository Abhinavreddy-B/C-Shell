#include "../headers.h"

int check_if_valid_syntax(char * input){
    int i=0;
    while(input[i]!='\0' && (input[i] == ' ' || input[i] == '\t' )){
        i++;
    }
    if(input[i] == ';' || input[i] == '&'){
        return -1;
    }
    for(;input[i]!='\0';i++){
        if(input[i] != ';' && input[i] != '&'){
            continue;
        }
        // printf("%c",input[i]);
        // int flag = 1;
        for(int j=i+1;input[j]!='\0';j++){
            if(input[j] == ' ' || input[j] == '\t'){
                continue;
            }else if(input[j]!=';'&& input[j]!='&'){
                break;
            }else if((input[i] == ';' && (input[j] == ';' || input[j] == '&')) || (input[i] == '&' && input[j] == '&')){
                return -1;
            }
        }
    }
    return 1;
}