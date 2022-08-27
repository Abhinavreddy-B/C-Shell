#include "../headers.h"
#include "../commands/cd.h"
#include "../commands/pwd.h"
#include "../commands/echo.h"
#include "../commands/ls.h"
#include "../out_module/print_error.h"

// void remove_unnecessary(char *s, char *helper_string)
// {
//     int start = 0;
//     while (s[start] == ' ' || s[start] == '\t')
//         start++;
//     strcpy(helper_string, s + start);
//     int pos = 0;
//     for (int i = 0; helper_string[i] != '\0'; i++)
//     {
//         if (helper_string[i] == '\t')
//             helper_string[i] = ' ';
//         if (i == 0 || helper_string[i] != ' ' || (helper_string[i] == ' ' && helper_string[i - 1] != ' '))
//         {
//             s[pos] = helper_string[i];
//             pos++;
//         }
//     }
//     s[pos] = '\0';
//     printf("%s\n",s);
// }


void splitter(char *command, size_t MAXIMUM_DIRECTORY_LENGTH,
              size_t MAXIMUM_INPUT_SIZE, const size_t MAXIMUM_ERROR_LENGTH,
              const size_t MAXIMUM_SYSTEM_NAME, char *username,
              char *home_directory, char *error_holder,
              char *relative_dir, char *absolute_dir, char* old_directory)
{
    size_t MAX_NO_OF_PARTS = 101LL;
    size_t MAXIMUM_NO_OF_INNER_FILES = 101LL;
    // printf("%s\n",command);
    char* command_split[MAX_NO_OF_PARTS];
    char* part;
    int cnt=0;
    part =  command_split[cnt] = strtok (command," \t");
    while(part!=NULL){
        cnt++;
        part = command_split[cnt] = strtok (NULL, " \t");
    }
    if(cnt == 0){
        return;
    }
    if(strcmp(command_split[0],"cd") == 0){
        if(cnt == 1){
            change_directory(absolute_dir,relative_dir,"~",home_directory, old_directory ,MAXIMUM_DIRECTORY_LENGTH);
        }else if(cnt != 2){
            print_error("Invalid No Of arguments");
            return;
        }else{
            change_directory(absolute_dir,relative_dir,command_split[1],home_directory, old_directory ,MAXIMUM_DIRECTORY_LENGTH);
        }
    }else if(strcmp(command_split[0],"pwd") == 0){
        present_working_directory(absolute_dir);
    }else if(strcmp(command_split[0],"echo")==0){
        echo(command_split,cnt);
    }else if(strcmp(command_split[0],"ls") == 0){
        ls(command_split,cnt,MAXIMUM_NO_OF_INNER_FILES);
    }
}

void shell_helper(char *input, size_t MAXIMUM_DIRECTORY_LENGTH,
                  size_t MAXIMUM_INPUT_SIZE, const size_t MAXIMUM_ERROR_LENGTH,
                  const size_t MAXIMUM_SYSTEM_NAME, char *username,
                  char *home_directory, char *error_holder,
                  char *relative_dir, char *absolute_dir, char* old_directory)
{
    // char input_temp[MAXIMUM_INPUT_SIZE];
    // remove_unnecessary(input,input_temp);
    size_t MAXIMUM_NO_OF_TOKENS = 101LL ;
    char* split_input[MAXIMUM_NO_OF_TOKENS];
    // printf("%s\n",input);
    char* token;
    int tokencnt=0;
    token = split_input[tokencnt] =strtok(input,";");
    while(token != NULL){
        tokencnt++;
        token = split_input[tokencnt] = strtok(NULL,";");
    }
    for(int i=0;i<tokencnt;i++){
        // printf ("%s\n",split_input[i]);
        splitter(split_input[i], MAXIMUM_DIRECTORY_LENGTH,
                  MAXIMUM_INPUT_SIZE, MAXIMUM_ERROR_LENGTH,
                  MAXIMUM_SYSTEM_NAME,username,
                  home_directory, error_holder,
                  relative_dir, absolute_dir,old_directory);
    }
}