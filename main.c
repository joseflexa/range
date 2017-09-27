#include <stdio.h>
#include <stdlib.h>

typedef struct range_t {
    int start;
    int end;
} range;
int cmpfunc (const void * a, const void * b) {
    range* ra = (range *)a;
    range* rb = (range *)b;
    return ra->start - rb->start;
}

int main(int argc, char *argv[])
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int index, lcount = 0;
    range* ranges;
    int rangesIndex = 0;

    if (argc < 3) {
        perror("range <file-path> range-start:range-end");
        exit(EXIT_FAILURE);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    ranges = (range *) malloc((sizeof (range)) * (argc - 2));
    for (index = 2;index < argc;index++) {
        int ret = sscanf(argv[index], "%d:%d", &ranges[index].start, &ranges[index].end);
        if (ret < 2 || ranges[index].start >= ranges[index].end) {
            perror("invalid start end values");
            exit(EXIT_FAILURE);
        }
        qsort(ranges, argc - 2, sizeof(range), cmpfunc);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        lcount++;
        while (lcount > rangesIndex) {
            rangesIndex++;
        }
        if (lcount >= ranges[rangesIndex].start && lcount <= ranges[rangesIndex].end) {
            printf("%s", line);
        }
    }

    fclose(fp);
    if (line) {
        free(line);
    }
    exit(EXIT_SUCCESS);
}