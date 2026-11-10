#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const size_t count = 3;
    int *values = malloc(count * sizeof *values);

    if (values == NULL) {
        fprintf(stderr, "malloc failed.\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        values[i] = (int)(i + 1) * 100;
    }

    printf("before free: %d %d %d\n",
           values[0], values[1], values[2]);

    free(values);
    values = NULL;

    if (values == NULL) {
        puts("values is NULL: do not access the array.");
    }

    free(values);
    puts("free(NULL) completed.");

    return 0;
}
