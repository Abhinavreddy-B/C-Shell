#include "../headers.h"
#include "../io_module/print_error.h"

extern size_t MAXIMUM_DIRECTORY_LENGTH;
extern size_t MAXIMUM_INNER_DIRECTORIES ;
extern char *home_directory;

void recursive_printer(char *path_abs,char* path_rel,int print_dirs,int print_files,char *target){
    DIR * dr = opendir(path_abs);
    struct dirent *prop;
    if(dr != NULL){
        if(print_dirs && target == NULL){
            printf("%s\n",path_rel);
        }
        while((prop = readdir(dr)) != NULL){
            if(strcmp(prop->d_name,".") != 0 && strcmp(prop->d_name,"..") != 0){
                int abs_len = strlen(path_abs);
                int rel_len = strlen(path_rel);
                strcat(path_abs, "/");
                strcat(path_abs, prop->d_name);
                strcat(path_rel, "/");
                strcat(path_rel, prop->d_name);
                if(target != NULL && strcmp(target,prop->d_name) == 0){
                    printf("%s\n",path_rel);
                }
                recursive_printer(path_abs, path_rel,print_dirs,print_files,target);
                path_abs[abs_len] = '\0';
                path_rel[rel_len] = '\0';
            }
            // free(prop);
        }
        closedir(dr);
    }else if(errno == ENOTDIR){
        if(print_files && target == NULL){
            printf("%s\n",path_rel);
        }
        return;
    }else{
        char error[101];
        sprintf(error,"%s is not a directory\n",path_rel);
        print_error(error);
        return;
    }
}

int discover_folder(char* command[],int cnt){
    char path[MAXIMUM_DIRECTORY_LENGTH];
    int print_dirs = 0;
    int print_files = 0;
    int iter = 1;
    int flags_exist = 0;
    if(cnt==1 || command[1][0]=='-'){
        strcpy(path,".");
    }else{
        strcpy(path,command[1]);
        iter++;
    }
    while(iter < cnt && command[iter][0] == '-'){
        if(strcmp(command[iter],"-f") == 0){
            print_files = 1;
            flags_exist =1;
        }else if(strcmp(command[iter],"-d") == 0){
            print_dirs = 1;
            flags_exist =1;
        }else if(strcmp(command[iter],"-fd") == 0 || strcmp(command[iter],"-df") == 0){
            print_files = 1;
            print_dirs = 1;
            flags_exist =1;
        }else if(command[iter][0]=='-'){
            char error[1001];
            sprintf(error,"Invalid Flag %s",command[iter]);
            print_error(error);
            return -1;
        }
        iter++;
    }
    if(print_dirs == 0 && print_files == 0){
        print_dirs = 1;
        print_files = 1;
    }
    char *target = NULL;
    if(iter < cnt){
        target = command[iter];
        iter++;
    }
    if(iter != cnt){
        print_error("Invalid Number Of Arguments for the command \"discover\"");
        return -1;
    }
    if(target != NULL && flags_exist == 1){
        print_error("Invalid use-case of \"discover\", cannot have both flags and target at the same time");
        return -1;
    }
    char scannabe_path_abs[MAXIMUM_DIRECTORY_LENGTH];
    char scannabe_path_rel[MAXIMUM_DIRECTORY_LENGTH];
    strcpy(scannabe_path_rel, path);
    if (path[0] == '~')
    {
        // printf("Hello\n");
        sprintf(scannabe_path_abs, "%s%s", home_directory, &path[1]);
    }
    else
    {
        strcpy(scannabe_path_abs, path);
    }
    // printf("%p\n",target);
    recursive_printer(scannabe_path_abs, scannabe_path_rel,print_dirs,print_files,target);
    return 0;
}