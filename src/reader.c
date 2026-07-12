#include <stdio.h>
#include <string.h>
#include "reader.h"
#include <stdlib.h>

char* read_file(const char *path) {

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", path);
        return NULL;
    }
    printf("Opened: %s\n", path);

    fseek(file, 0,SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char*file_content = malloc(file_size+1);
    if (file_content == NULL) {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return NULL;
    }
    size_t bytes_read = fread(file_content, 1, file_size, file);

    if (bytes_read != (size_t)file_size) {
        printf("Failed to read entire file: %s\n", path);
        free(file_content);
        fclose(file);
        return NULL;
    }
    file_content[file_size] = '\0';

    fclose(file);

    return file_content;
}