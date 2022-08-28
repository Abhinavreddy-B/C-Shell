#include "../headers.h"
#include "../out_module/print_error.h"

int is_directory(const char *fileName){
    struct stat path;
    stat(fileName, &path);
    if (stat(fileName, &path) == -1){
        return -1;
    }
    return S_ISDIR(path.st_mode);
}

int change_directory(char *absolute_path, char *relative_path, char *input, char *home_path, char* old_directory, size_t MAXIMUM_DIRECTORY_LENGTH){
    char new_dir[MAXIMUM_DIRECTORY_LENGTH];
    if(input[0]== '~'){
        sprintf(new_dir,"%s%s",home_path,(input+1));
    }else if(input[0] == '-'){
        if(old_directory[0] == '\0'){
            print_error("OLDPWD not set");
            return 0;
        }
        sprintf(new_dir,"%s%s",old_directory,(input+1));
    }
    else{
        strcpy(new_dir,input);
    }
    int retvalue = chdir(new_dir);
    if(retvalue == 0){
        strcpy(old_directory,absolute_path);
        absolute_path = getcwd(absolute_path,MAXIMUM_DIRECTORY_LENGTH);
        if(strncmp(absolute_path,home_path,strlen(home_path)) == 0){
            sprintf(relative_path,"~%s",&absolute_path[strlen(home_path)]);
        }else{
            strcpy(relative_path,absolute_path);
        }
    }else{
        perror("\033[0;31mError ");
    }
    return 1;
}