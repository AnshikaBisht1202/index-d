#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include <sys/stat.h>
#include "reader.h"

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
            if (stat(path, &info) != 0) {
                printf("Failed to stat %s\n", path);
                continue;
            }

            if (S_ISDIR(info.st_mode)) {
                scan_directory(path);
            }
            else {
                read_file(path);

            }
            
        }
    }
    
    closedir(dir);
}
