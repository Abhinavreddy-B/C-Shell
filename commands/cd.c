#include "../headers.h"
#include "../out_module/print_error.h"
#include "commands.h"

extern size_t MAXIMUM_DIRECTORY_LENGTH;
extern char *home_directory;
extern char *relative_dir;
extern char *absolute_dir;
extern char *prev_directory;

int change_directory(char *input){
    char new_dir[MAXIMUM_DIRECTORY_LENGTH];
    if(input[0]== '~'){
        sprintf(new_dir,"%s%s",home_directory,(input+1));
    }else if(input[0] == '-'){
        if(input[1]!='\0'){
            print_error("Unsupported Path\n");
            return 1;
        }
        if(prev_directory[0] == '\0'){
            print_error("OLDPWD not set");
            return 0;
        }
        sprintf(new_dir,"%s%s",prev_directory,(input+1));
        printf("%s\n",new_dir);
    }
    else{
        strcpy(new_dir,input);
    }
    int retvalue = chdir(new_dir);
    if(retvalue == 0){
        strcpy(prev_directory,absolute_dir);
        absolute_dir = getcwd(absolute_dir,MAXIMUM_DIRECTORY_LENGTH);
        if(strncmp(absolute_dir,home_directory,strlen(home_directory)) == 0){
            sprintf(relative_dir,"~%s",&absolute_dir[strlen(home_directory)]);
        }else{
            strcpy(relative_dir,absolute_dir);
        }
    }else{
        perror("\033[0;31mError ");
    }
    return 1;
}