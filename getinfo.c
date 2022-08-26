#include "headers.h"

int get_username(char** username_ptr,char errors[]){
    *username_ptr = getlogin();
    if(*username_ptr == NULL){
        perror("Error");
        sprintf(errors , "\033[0;31mSome Problem Occured while getting user details\n\033[m");
        return 1;
    }
    return 0;
}

int get_systemname(char* system_name,char errors[]){
    struct utsname system_details;
    if (uname(&system_details) == -1)
    {
        perror("Error");
        sprintf(errors , "\033[0;31mSome Problem Occured while getting system details\n\033[m");
        return 1;
    }
    strcpy(system_name,system_details.nodename);
    return 0;
}

int get_home_dir(char** home_directory_ptr,size_t MAXIMUM_DIRECTORY_LENGTH,char errors[]){
    char * t = (*home_directory_ptr = getcwd(*home_directory_ptr,MAXIMUM_DIRECTORY_LENGTH));
    if(t == NULL){
        perror("Error");
        sprintf(errors , "\033[0;31mCouldnt get the current directory\n\033[m");
        return 1;
    }
    return 0;
}