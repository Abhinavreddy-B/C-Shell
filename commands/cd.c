#include "../headers.h"
#include "../out_module/print_error.h"

void find_new_path(char *path)
{
    if(strcmp(path,"/") == 0){
        return;
    }
    if(strcmp(path,"/home") == 0){
        sprintf(path,"/");
        return;
    }
    int len = strlen(path);
    len--;
    while (path[len] != '/')
        len--;
    path[len] = '\0';
}

int is_directory(const char *fileName)
{
    struct stat path;

    stat(fileName, &path);
    if (stat(fileName, &path) == -1)
    {
        return -1;
    }

    return S_ISDIR(path.st_mode);
}

/* int change_directory(char *absolute_path, char *relative_path, char *input, char *home_path, size_t MAXIMUM_DIRECTORY_LENGTH)
{
    // printf("%s\n", input);
    if (input[0] == '~'&&input[1]== '\0')
    {
        sprintf(relative_path, "~");
        sprintf(absolute_path, "%s", home_path);
        return 1;
    }
    if (input[0] == '.' && input[1] == '\0')
    {
        return 1;
    }
    if (input[0] == '.' && input[1] == '.' && input[2] == '\0')
    {
        if (strcmp(relative_path, "~") == 0)
        {
            find_new_path(absolute_path);
            strcpy(relative_path, absolute_path);
            return 1;
        }
        else if (strcmp(relative_path, "/home") == 0 || strcmp(relative_path, "/") == 0)
        {
            relative_path[1] = '\0';
            absolute_path[1] = '\0';
            return 1;
        }
        else
        {
            find_new_path(relative_path);
            find_new_path(absolute_path);
            return 1;
        }
    }
    else
    {
        char new_relative_dir[MAXIMUM_DIRECTORY_LENGTH];
        char new_absolute_dir[MAXIMUM_DIRECTORY_LENGTH];
        // printf("%p\n", input);
        // printf("Here\n");
        if (strcmp(absolute_path, "/") == 0)
        {
            sprintf(new_absolute_dir, "/%s", input);
        }
        else
        {
            sprintf(new_absolute_dir, "%s/%s", absolute_path, input);
        }
        // printf("%s\n",new_dir);
        // printf("%p\n", input);
        int ret_val = is_directory(new_absolute_dir);
        if (ret_val == -1)
        {
            print_error("No such file or directory");
            return 0;
        }
        else if (ret_val == 0)
        {
            char error[50];
            sprintf(error,"%s is not a directory",input);
            print_error(error);
            return 0;
            // printf("%d\n",ret_val);
        }
        else
        {
            if (strcmp(absolute_path, "/") == 0)
            {
                sprintf(new_relative_dir, "/%s", input);
                sprintf(new_absolute_dir, "/%s", input);
            }
            else
            {
                sprintf(new_relative_dir, "%s/%s", relative_path, input);
                sprintf(new_absolute_dir, "%s/%s", absolute_path, input);
            }
            // printf("%s\n",new_relative_dir);
            strcpy(absolute_path, new_absolute_dir);
            strcpy(relative_path, new_relative_dir);
        }
        return 1;
    }
}*/



int change_directory(char *absolute_path, char *relative_path, char *input, char *home_path, size_t MAXIMUM_DIRECTORY_LENGTH){
    if(input[0] == '/'){
        int ret_val = is_directory(input);
        if (ret_val == -1)
        {
            print_error("No such file or directory");
            return 0;
        }
        else if (ret_val == 0)
        {
            char error[50];
            sprintf(error,"%s is not a directory",input);
            print_error(error);
            return 0;
        }else{
            strcpy(absolute_path,input);
            if(strncmp(input,home_path,strlen(home_path)) == 0){
                sprintf(relative_path,"~%s",&input[strlen(home_path)]);
            }else{
                strcpy(relative_path,absolute_path);
            }
        }
    }else{
        char* next_dest = strtok(input,"/");
        char Final_new_Path[MAXIMUM_DIRECTORY_LENGTH];
        strcpy(Final_new_Path,absolute_path);
        while(next_dest != NULL){
            if(strcmp(next_dest,"~") == 0){
                sprintf(Final_new_Path,"%s",home_path);
            }else if(strcmp(next_dest,"..") == 0){
                find_new_path(Final_new_Path);
            }else if(strcmp(next_dest,".") == 0){
                // do nothing
            }else{
                strcat(Final_new_Path,"/");
                strcat(Final_new_Path,next_dest);
                int exists = is_directory(Final_new_Path);
                if (exists == -1)
                {
                    print_error("No such file or directory");
                    return 0;
                }
                else if (exists == 0)
                {
                    char error[50];
                    sprintf(error, "%s is not a directory", input);
                    print_error(error);
                    return 0;
                }
            }
            next_dest = strtok(NULL,"/");
        }
        strcpy(absolute_path, Final_new_Path);
        if (strncmp(Final_new_Path, home_path, strlen(home_path)) == 0)
        {
            sprintf(relative_path, "~%s", &Final_new_Path[strlen(home_path)]);
        }
        else
        {
            strcpy(relative_path, absolute_path);
        }
    }
}