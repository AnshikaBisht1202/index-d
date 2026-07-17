#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include <sys/stat.h>
#include "reader.h"
#include <stdlib.h>
#include <chunker.h>

static int should_skip(const char *name) {

    if (strcmp(name, ".") == 0) return 1;
    if (strcmp(name, "..") == 0) return 1;
    if (strcmp(name, ".git") == 0) return 1;

    return 0;
}

void scan_directory(const char *directory) {

    DIR *dir = opendir(directory);
    
    if (dir == NULL){
        printf("Failed to open directory.\n");
        return;
    }
    printf("Scanning directory: %s\n\n", directory);

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        
        if (should_skip(entry->d_name)) {
            continue;
        } 

            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

            struct stat info;
          
            if (stat(path, &info) != 0) {
                printf("Failed to stat %s\n", path);
                continue;
            }

            if (S_ISDIR(info.st_mode)) {
                scan_directory(path);
            }
            else {
                char *contents = read_file(path);
                if (contents != NULL) {
                    chunk_file(path, contents);
                    free(contents);
                }

            }
            
    }
    
    closedir(dir);
}
