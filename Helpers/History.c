#include "../headers.h"

extern size_t MAXIMUM_INPUT_SIZE;

int load_to_history(FILE* input, char* history[20],char* previous_command){
    int cnt=0;
    while(fscanf(input,"%[^\n]s",history[cnt]) != EOF && cnt <=20 && history[cnt] != NULL){
        strcpy(previous_command,history[cnt]);
        fgetc(input);
        cnt++;
    }
    return cnt;
}

void add_to_history(char *command, char* history[20],FILE* output,int* no_of_existing_history){
    if(*no_of_existing_history < 20){
        strcpy(history[*no_of_existing_history],command);
        for(int i=0;i<=(*no_of_existing_history);i++){
            fprintf(output,"%s\n",history[i]);
        }
        (*no_of_existing_history)++;
        return;
    }
    free(history[0]);
    fseek(output,0,SEEK_SET);
    for(int i=0;i<19;i++){
        history[i] = history[i+1];
        fprintf(output,"%s\n",history[i]);
    }
    history[19] = (char *) malloc(MAXIMUM_INPUT_SIZE * sizeof(char));
    strcpy(history[19],command);
    fprintf(output,"%s\n",history[19]);
}