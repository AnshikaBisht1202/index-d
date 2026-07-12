#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include <sys/stat.h>

void scan_directory(const char *directory) {

    DIR *dir = opendir(directory);
    
    if (dir == NULL){
        printf("Failed to open directory.\n");
        return;
    }
    printf("Scanning directory: %s\n", directory);

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

            struct stat info;
            stat(path, &info);

            if (S_ISDIR(info.st_mode)) {
                scan_directory(path);
            }
            else {
                printf("%s\n", path);
            }
            
        }
    }
    
    closedir(dir);
}
