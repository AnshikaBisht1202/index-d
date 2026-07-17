#ifndef CHUNKER_H
#define CHUNKER_H

#define MAX_PATH_LENGTH 1024
#define MAX_CHUNK_SIZE 500

typedef struct {
    char path[MAX_PATH_LENGTH];
    int chunk_number;
    int text_length;
    char text[MAX_CHUNK_SIZE + 1];
} Chunk;

int chunk_file(const char *path, const char *contents);

#endif