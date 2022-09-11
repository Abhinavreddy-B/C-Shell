#include "../headers.h"
#include "./input.h"
#include "../io_module/prompt.h"

extern char *input;
extern const size_t MAXIMUM_INPUT_SIZE;

struct termios orig_termios;

void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void update(char * matched_files[],int cnt,char name[],int len_name){
    int len = len_name;
    while(1){
        if(matched_files[0][len] == '\0'){
            strcat(input,&name[len_name]);
            return;
        } 
        char ch = matched_files[0][len];
        for(int i=0;i<cnt;i++){
            if(matched_files[i][len] != ch){
                strcat(input,&name[len_name]);
                return;
            }
        }
        name[len] = ch;
        name[len+1] = '\0';
        len++;
    }
}

void handletab(char parent[],char name[],int len_name){
    if(parent[0] == '\0'){
        parent[0] = '.';
        parent[1] = '\0';
    }
    // printf("\'%s\' - \'%s\'",parent,name);
    DIR* d;
    if((d = opendir(parent)) != NULL){
        // printf("Hello\n");
        struct dirent** files;
        int cnt = scandir(parent,&files,NULL,alphasort);
        int matched = 0;
        for(int i=0;i<cnt;i++){
            matched += (len_name == 0 || strncmp(files[i]->d_name,name,len_name) == 0);
        }
        if(matched == 0){
            printf("\n\033[31;1mNo Matching Files\n\033[0m");
        }else if(matched == 1){
            for(int i=0;i<cnt;i++){
                if(len_name == 0 || strncmp(files[i]->d_name,name,len_name) == 0){
                    strcat(parent,"/");
                    strcat(parent,files[i]->d_name);
                    strcat(input,&files[i]->d_name[len_name]);
                    struct stat props;
                    stat(parent,&props);
                    if(S_ISDIR(props.st_mode)){
                        strcat(parent,"/");
                        strcat(input,"/");
                    }else{
                        strcat(input," ");
                        parent[0] = '\0';
                    }
                    name[0] = '\0';
                    return;
                };
            }
        }else{
            char * matched_files[matched];
            int pt=0;
            printf("\n");
            for(int i=0;i<cnt;i++){
                if(len_name == 0 || strncmp(files[i]->d_name,name,len_name) == 0){
                    char temp[MAXIMUM_INPUT_SIZE];
                    sprintf(temp,"%s/%s",parent,files[i]->d_name);
                    struct stat props;
                    stat(temp,&props);
                    // printf("%d\n",S_ISDIR(props.st_mode));
                    if(__S_IFDIR == ( __S_IFMT & props.st_mode) ){
                        printf("%s/\n",files[i]->d_name);
                    }else{
                        printf("%s\n",files[i]->d_name);
                    }
                    matched_files[pt] = files[i]->d_name;
                    pt++;
                };
            }
            update(matched_files,matched,name,len_name);
        }
    }
}

void take_input()
{
    enableRawMode();
    char c;
    int pt = 0;
    char temp_name[MAXIMUM_INPUT_SIZE];
    temp_name[0] = '\0';
    char temp_parent[MAXIMUM_INPUT_SIZE];
    // temp_parent[0] = '.';
    temp_parent[0] = '\0';
    int pt2 = 0;
    prompt();
    fflush(stdout);
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (iscntrl(c))
        {
            if (c == 10)
                break;
            else if (c == 27)
            {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2)
                { // length of escape code
                    printf("\rarrow key: %s", buf);
                }
            }
            else if (c == 127)
            { // backspace
                if (pt > 0)
                {
                    if (input[pt - 1] == 9)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            printf("\b");
                        }
                    }
                    input[--pt] = '\0';
                    printf("\b \b");
                }
                // printf("%c",8); // backspace character
                // input[strlen(input) - 1] = '\0';
                // input[strlen(input)+1] = ' ';
            }
            else if (c == 9)
            { // TAB character
                handletab(temp_parent,temp_name,strlen(temp_name));
                pt2 = strlen(temp_name);
                pt = strlen(input);
            }
            else if (c == 4)
            {
                exit(0);
            }
            else
            {
                printf("%d\n", c);
            }
        }
        else
        {
            input[pt++] = c;
            input[pt] = '\0';
            printf("%c", c);
            if(c == ' '){
                // temp_parent[0] = '.';
                temp_parent[0] = '\0';
                // pt2 = 1;
                temp_name[0] = '\0';
                pt2 = 0;
            }
            else if(c == '/'){
                strcat(temp_parent,"/");
                strcat(temp_parent,temp_name);
                temp_name[0] = '\0'; 
                pt2 = 0;
            }else{
                temp_name[pt2] = c;
                pt2++;
                temp_name[pt2] = '\0';
            }
        }
        prompt();
        fflush(stdout);
    }
    disableRawMode();
}