#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *value = malloc(sizeof *value);
    if (value == NULL) {
        return 1;
    }
    *value = 100;
    int *alias = value;

    printf("value: %d\n", *value);
    printf("alias: %d\n", *alias);

    free(value);
    value = NULL;
    alias = NULL;

    puts("released; both pointers set to NULL");
    return 0;
}
