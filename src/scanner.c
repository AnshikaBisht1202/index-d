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

static int supported_file(const char *name) {

    const char *ext = strrchr(name, '.');

    if (ext == NULL) {
        return 0;
    }

    if (strcmp(ext, ".c") == 0) return 1;
    if (strcmp(ext, ".h") == 0) return 1;
    if (strcmp(ext, ".md") == 0) return 1;
    if (strcmp(ext, ".txt") == 0) return 1;
    if (strcmp(ext, ".py") == 0) return 1;
    if (strcmp(ext, ".json") == 0) return 1;
    if (strcmp(ext, ".yml") == 0) return 1;
    if (strcmp(ext, ".yaml") == 0) return 1;

    return 0;
}

int scan_directory(const char *directory) {

    DIR *dir = opendir(directory);
    
    if (dir == NULL){
        printf("Failed to open directory.\n");
        return 1;
    }
    printf("Scanning directory: %s\n", directory);

    struct dirent *entry;

    int total_chunks = 0;

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

                if (!supported_file(entry->d_name)) {
                    continue;
                }

                char *contents = read_file(path);

                if (contents != NULL) {
                    total_chunks = chunk_file(path, contents);
                    free(contents);
                }
            }
            
    }
    
    closedir(dir);

    return total_chunks;
}
