#include <stdio.h>
#include "vector_store.h"

void save_chunk(Chunk *chunk) {

    FILE *file = fopen("data/chunks.bin", "ab");

    if (file == NULL) {
        printf("Failed to open chunks.bin\n");
        return;
    }

    fwrite(chunk, sizeof(Chunk), 1, file);

    fclose(file);
}