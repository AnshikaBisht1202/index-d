#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "scanner.h"

int cli_run(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage:\n./askie index <directory>\n./askie ask <question>\n");
        return 1;
    }

    if (strcmp(argv[1], "index") == 0) {
        if (argc > 2) {
            remove("data/chunks.bin");
            int total = scan_directory(argv[2]);
            printf("\nIndexed %d chunks.\n", total);
            return 0;
        }
        else {
            printf("Please provide a repository to index.\n");
            return 12;
        }
    }
    else if (strcmp(argv[1], "ask") == 0) {
        if (argc > 2) {
            char ques[512] = "";
            int num = argc - 2;
            for (int i = 0; i < num; i++) {
                strcat(ques, argv[i + 2]);
                strcat(ques, " ");
            }
            printf("Question : %s\n", ques);
            return 0;
        }
        else {
            printf("Please provide a question to ask.\n");
            return 4;
        }
    }
    else {
        printf("Unknown command: %s\n", argv[1]);
        return 6;
    }
    
    return 0;
}


