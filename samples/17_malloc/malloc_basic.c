#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mdump.h"

int main(void)
{
    const size_t count = 3;
    int *values = malloc(count * sizeof *values);

    if (values == NULL) {
        fprintf(stderr, "malloc failed.\n");
        return 1;
    }

    memset(values, 0, count * sizeof *values);
    printf("after memset: %d %d %d\n",
           values[0], values[1], values[2]);
    mdump(values, count * sizeof *values);

    values[0] = 100;
    values[1] = 200;
    values[2] = 300;
    printf("malloc + assignment: %d %d %d\n",
           values[0], values[1], values[2]);
    mdump(values, count * sizeof *values);

    free(values);
    values = NULL;

    values = calloc(count, sizeof *values);
    if (values == NULL) {
        fprintf(stderr, "calloc failed.\n");
        return 1;
    }

    printf("calloc: %d %d %d\n",
           values[0], values[1], values[2]);
    mdump(values, count * sizeof *values);

    free(values);
    values = NULL;
    return 0;
}
