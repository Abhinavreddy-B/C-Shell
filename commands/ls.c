#include "../headers.h"
#include "./commands.h"
#include "../io_module/print_error.h"

extern size_t MAXIMUM_DIRECTORY_LENGTH;
extern char *home_directory;

static int cmp(const void* a,const void* b){
    char * n1 = (char *) (*((struct dirent **) a))->d_name;
    char * n2 = (char *) (*((struct dirent **) b))->d_name;
    return strcasecmp(n1,n2);
}

static void sort(struct dirent* arr[],int cnt){
    qsort(arr,cnt,sizeof(struct dirent*),cmp);
}

int masks[3][3] = {{S_IRUSR,S_IWUSR,S_IXUSR},{S_IRGRP,S_IWGRP,S_IXGRP},{S_IROTH,S_IWOTH,S_IXOTH}};
char depiction[3] = {'r','w','x'};

static void print_Format_permissions(ino_t perms,int is_directory,int is_link){
    char str[11];
    str[10]='\0';
    if(is_directory){
        str[0] = 'd';
    }else if(is_link){
        str[0] = 'l';
    }else
    {
        str[0]='-';
    }
    for(int i=0;i<9;i++){
        if( perms & masks[i/3][i%3]){
            str[i+1] = depiction[i%3];
        }else{
            str[i+1] = '-';
        }
    }
    printf("%10s ",str);
}

/**
 * @param mode 0 =>normal file , 1 => directory, 2 => executables
*/
static void print_name(char* name,int mode){
    // normal file
    if(mode == 0){
        printf("%s",name);
    }else if(mode==1){
        // directory
        printf("\033[34m\033[1m%s\033[0m",name);
    }else if(mode == 2){
        //executables
        printf("\033[32m\033[1m%s\033[0m",name);
    }
    printf("\n");
}

static void print_detail(char* name,struct stat file_props){
    print_Format_permissions(file_props.st_mode,S_ISDIR(file_props.st_mode),S_ISLNK(file_props.st_mode));
    printf("%5ld ",file_props.st_nlink);
    printf("%-16.15s ", getpwuid(file_props.st_uid)->pw_name);
    printf("%-16.15s ", getgrgid(file_props.st_gid)->gr_name);
    printf("%8ld ",file_props.st_size);
    
    time_t curr_time = time(NULL);
    struct tm* current_time_format = localtime(&curr_time);
    int monthes = ( (current_time_format->tm_year)*12 + current_time_format->tm_mon );
    struct tm * timeinfo;
    timeinfo = localtime (&(file_props.st_mtim.tv_sec));

    char buff[35];
    if( monthes - timeinfo->tm_year*12 - timeinfo->tm_mon > 6){
        strftime(buff, sizeof(buff), "%b %d %Y", timeinfo);
    }else{
        strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);
    }

    printf("%s ",buff);
    if( S_ISDIR( file_props.st_mode ) != 0){
        print_name(name,1);
    }else if( file_props.st_mode & S_IXUSR){
        print_name(name,2);
    }else{
        print_name(name,0);
    }
}

static int cnt_total(char* path , struct dirent **files,int hidden,int cnt){
    int total = 0;
    for (int i = 0; i < cnt; i++){
        if (hidden == 1 || files[i]->d_name[0] != '.' ){
            struct stat file_props;
            char temp[10000];
            sprintf(temp,"%s/%s",path,files[i]->d_name);
            lstat(temp,&file_props);
            total += file_props.st_blocks;
        }
    }
    return total;
}
// mode = 0 means brief , mode = 1 means detail
// many is 1 when there are more than 1 paths to be printed, else many is 0
static int print_ls_helper(char *path_input,size_t MAXIMUM_NO_OF_INNER_PARTS, int hidden, int mode,int many )
{
    char path[MAXIMUM_DIRECTORY_LENGTH] ;
    if(path_input[0] == '~'){
        sprintf(path , "%s%s", home_directory, &path_input[1]);
    }else{
        strcpy(path,path_input);
    }
    struct dirent **files;
    int cnt = 0;
    cnt = scandir(path,&files,NULL,alphasort);
    if (cnt != -1)
    {
        // printf("inside\n");
        if(many){
            printf("\n\033[41:32m%s:\033[0m\n",path);
        }
        sort(files, cnt);
        if (mode == 0){
            for (int i = 0; i < cnt; i++){
                if (hidden == 1 || files[i]->d_name[0] != '.'){
                    struct stat file_props;
                    char temp[10000];
                    sprintf(temp,"%s/%s",path,files[i]->d_name);
                    lstat(temp,&file_props);
                    if(S_ISDIR(file_props.st_mode) != 0){
                        print_name(files[i]->d_name, 1);
                    }else if (file_props.st_mode & S_IXUSR){
                        print_name(files[i]->d_name, 2);
                    }else{
                        print_name(files[i]->d_name, 0);
                    }
                    // printf("\n");
                    // printf("%s\t", files[i]->d_name);
                }
            }
            // printf("\n");
        }else{
            struct stat dirstats;
            lstat(path,&dirstats);
            printf("total %d\n",cnt_total(path,files,hidden,cnt)/2);
            for (int i = 0; i < cnt; i++){
                if (hidden == 1 || files[i]->d_name[0] != '.'){
                    struct stat file_props;
                    char temp[10000];
                    sprintf(temp,"%s/%s",path,files[i]->d_name);
                    lstat(temp,&file_props);
                    print_detail(files[i]->d_name,file_props);
                }
            }
        }
        // closedir(directory);
    }else if(errno == ENOTDIR){
        // printf("Double\n");
        if(many){
            printf("\n");
        }
        // struct dirent *file = readdir(directory);
        char name[100000];
        // int start=strlen(path)-1;
        // while(path[start]!='/'&&start>=0) start--;
        strcpy(name,path);
        // printf("Hello\n");
        struct stat file_props;

        lstat(path,&file_props);
        if (mode == 0){
            if( file_props.st_mode & S_IXUSR ){
                print_name(name, 2);
            }else{
                print_name(name,0);
            }
            // printf("\n");
        }else{ 
            print_detail(name,file_props);
        }
    }else{
        print_error("Could not look-up for the file/directory");
        perror("\033[0;31mError ");
        return 1;
    }
    return 0;
}

int ls(char* command[],int cnt,size_t MAXIMUM_NO_OF_INNER_PARTS){
    // printf("Hello\n");
    int hidden = 0;
    int mode = 0;
    char* total_list[MAXIMUM_NO_OF_INNER_PARTS];
    int total_paths=0;
    for(int i=1;i<cnt;i++){
        if(strcmp(command[i],"-a") == 0){
            hidden = 1;
        }else if(strcmp(command[i],"-l") == 0){
            mode = 1;
        }else if(strcmp(command[i],"-la") == 0 || strcmp(command[i],"-al") == 0){
            hidden = 1;
            mode = 1;
        }else if(command[i][0] == '-'){
            print_error("Invalid flags");
            return 1;
        }else{
            total_list[total_paths] = command[i];
            total_paths++;
        }
    }
    if(total_paths == 0){
        print_ls_helper(".",MAXIMUM_NO_OF_INNER_PARTS,hidden,mode,0);
        return 0;
    }
    // printf("%d\n",total_paths);
    for(int i=0;i<total_paths;i++){
        // printf("\nstart\n");
        print_ls_helper(total_list[i],MAXIMUM_NO_OF_INNER_PARTS,hidden,mode,(total_paths != 1));
        // printf("\nend\n");
    }
    return 0;
}