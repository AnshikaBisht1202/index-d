#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *text;
    char *path;
    int chunk_number;
} Chunk;

void chunk_file(const char *path, const char *contents) {

    long len = strlen(contents);

    int offset = 0;

    const int chunk_size = 500;

    while (offset < len) {
        int remaining = len - offset;

        int actual_chunk_size;

        if (remaining > chunk_size) {
            actual_chunk_size = chunk_size;
        }
        else {
            actual_chunk_size = remaining;
        }

        char *chunk = malloc(actual_chunk_size + 1);
        memcpy(chunk, contents + offset, actual_chunk_size);
        chunk[actual_chunk_size] = '\0';
        printf("\n\nCHUNK\n\n");
        printf("%s", chunk);
        free(chunk);
        offset += actual_chunk_size;
    }

}