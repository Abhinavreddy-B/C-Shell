#include "../headers.h"

extern size_t MAXIMUM_INPUT_SIZE;

int load_to_history(FILE* input, char* history[20]){
    int cnt=0;
    while(scanf("%[^\n]s",history[cnt]) != EOF){
        fgetc(input);
        cnt++;
    }
    fseek(input,0,SEEK_SET);
    return 0;
}

int add_to_history(char *command, char* history[20],FILE* output){
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

int History_command()