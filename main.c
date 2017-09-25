#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int index;
    int start, end, lcount = 0;
    
    if (argc < 3) {
        perror("range <file-path> range-start:range-end");
        exit(EXIT_FAILURE);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    sscanf(argv[2], "%d:%d", &start, &end);
    if (start >= end) {
        perror("invalid start end values");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        lcount++;
        if (lcount >= start && lcount <= end) {
            printf("%s", line);            
        }
    }

    fclose(fp);
    if (line) {
        free(line);        
    }
    exit(EXIT_SUCCESS);
}