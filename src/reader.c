#include <stdio.h>
#include <string.h>
#include "reader.h"

void read_file(const char *path) {

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", path);
        return;
    }
    printf("Opened: %s\n", path);
    fclose(file);
}