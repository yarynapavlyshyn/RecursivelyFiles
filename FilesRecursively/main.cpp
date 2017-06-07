#include <iostream>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int is_directory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return not S_ISREG(path_stat.st_mode);
}

int func(int depth=0){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir) {
        perror("diropen");
        exit(1);
    };

    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }
        for(int i=0; i<depth; i++){
            std::cout << "--";
        }
        std::cout << "->";
        std::cout << entry->d_name << std::endl;
        if(is_directory(entry->d_name)){
            chdir(entry->d_name);
            func(depth+1);
            chdir("..");
        }
    };

    closedir(dir);
}

int main(int argc, char *argv[]){
    func();
}