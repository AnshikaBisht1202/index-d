#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chunker.h"
#include "vector_store.h"

int chunk_file(const char *path, const char *contents) {

    long len = strlen(contents);

    int offset = 0;

    int chunk_number = 0;

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

        if (chunk == NULL) {
            printf("Failed to allocate memory.\n");
            return 1;
        }

        Chunk current;

        memcpy(chunk, contents + offset, actual_chunk_size);
        chunk[actual_chunk_size] = '\0';

        strcpy(current.path, path);
        current.chunk_number = chunk_number;
        current.text_length = actual_chunk_size;
        strcpy(current.text, chunk);

        save_chunk(&current);
        free(chunk);

        offset += actual_chunk_size;
        chunk_number += 1;
    }

    return chunk_number + 1;
}