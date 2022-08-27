#include "../headers.h"
#include "../out_module/print_error.h"

int masks[3][3] = {{S_IRUSR,S_IWUSR,S_IXUSR},{S_IRGRP,S_IWGRP,S_IXGRP},{S_IROTH,S_IWOTH,S_IXOTH}};
char depiction[3] = {'r','w','x'};

int cmp(const void* a,const void* b){
    char * n1 = (char *) (*((struct dirent **) a))->d_name;
    char * n2 = (char *) (*((struct dirent **) b))->d_name;
    // printf("%s %s\n", (char *) n1, (char *)  n2);
    return strcmp(n1,n2);
}

void sort(struct dirent* arr[],int cnt){
    // for(int i=0;i<cnt;i++){
        // printf("%s\n",arr[i]->d_name);
    // }
    qsort(arr,cnt,sizeof(struct dirent*),cmp);
}

void print_Format_permissions(ino_t perms,unsigned char  d_type){
    char str[11];
    str[10]='\0';
    if(d_type == DT_DIR){
        str[0] = 'd';
    }else{
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

// void print_name(char* name,int is_directory){
    // if(is_directory){
        // printf("%s",name);
    // }else{
        // 
    // }
// }

void print_detail(struct dirent *file){
    print_Format_permissions(file->d_ino,file->d_type);
    struct stat file_props;
    stat(file->d_name,&file_props);
    // perror("Hello");
    printf("%4ld ",file_props.st_nlink);

    printf("%-15.15s ", getpwuid(file_props.st_uid)->pw_name);
    printf("%-15.15s ", getgrgid(file_props.st_gid)->gr_name);
    printf("%6ld ",file_props.st_size);
    // printf("%s ",file_props->st_mtim.tv_sec);
    printf("%s\n",file->d_name);
}

// mode = 0 means brief , mode = 1 means detail
int print_ls_normal(char *path,size_t MAXIMUM_NO_OF_INNER_PARTS, int hidden, int mode )
{
    // printf("%s\n",path);
    DIR *directory;
    struct dirent *prop;
    directory = opendir(path);
    if (directory != 0)
    {
        struct dirent *files[MAXIMUM_NO_OF_INNER_PARTS];
        int cnt = 0;
        while ((files[cnt] = prop = readdir(directory)) != NULL)
        {
            cnt++;
        }
        sort(files, cnt);
        if (mode == 0)
        {
            for (int i = 0; i < cnt; i++)
            {
                if (hidden == 1 || files[i]->d_name[0] != '.')
                {
                    printf("%s\t", files[i]->d_name);
                }
            }
            printf("\n");
        }else{
            for (int i = 0; i < cnt; i++)
            {
                if (hidden == 1 || files[i]->d_name[0] != '.')
                {
                    print_detail(files[i]);
                }
            }
        }
        closedir(directory);
    }
    else
    {
        print_error("Could not open the directory");
        perror("\033[0;31mError ");
        return 1;
    }
    return 0;
}

int ls(char* command[],int cnt,size_t MAXIMUM_NO_OF_INNER_PARTS){
    // if(cnt == 1){
        // print_ls_normal(".",MAXIMUM_NO_OF_INNER_PARTS,0,0);
    // }else if(cnt == 2){
        // if(command[1][0] == '-'){
            // if(strcmp(command[1],"-a") == 0){
                // print_ls_normal(".",MAXIMUM_NO_OF_INNER_PARTS,1,0);
            // }else if(strcmp(command[1],"-al") == 0 || strcmp(command[1],"-la") == 0){
                // print_ls_normal(".",MAXIMUM_NO_OF_INNER_PARTS,1,1);
            // }else if(strcmp(command[1],"-l") == 0){
                // print_ls_normal(".",MAXIMUM_NO_OF_INNER_PARTS,0,1);
            // }else{
                // print_error("Use of Unknown Flag");
            // }
        // }else{
            // print_ls_normal(command[1],MAXIMUM_NO_OF_INNER_PARTS,0,0);
        // }
    // }else if(cnt == 3){
        // 
    // }
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
            break;
        }else if(command[i][0] == '-'){
            print_error("Invalid flags");
            return 1;
        }else{
            total_list[total_paths] = command[i];
            total_paths++;
        }
    }
    if(total_paths == 0){
        print_ls_normal(".",MAXIMUM_NO_OF_INNER_PARTS,hidden,mode);
    }
    for(int i=0;i<total_paths;i++){
        print_ls_normal(total_list[i],MAXIMUM_NO_OF_INNER_PARTS,hidden,mode);
    }
    return 0;
}