#include <stdio.h>
#include <stdlib.h>

void show_local(void)
{
    int local_value = 100;

    printf("show_local: local_value = %d\n", local_value);
}

int *create_value(void)
{
    int *ptr = malloc(sizeof *ptr);

    if (ptr == NULL) {
        return NULL;
    }

    *ptr = 200;
    printf("create_value: *ptr = %d\n", *ptr);

    return ptr;
}

int main(void)
{
    show_local();
    puts("main: show_local returned");

    int *heap_ptr = create_value();

    if (heap_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    puts("main: create_value returned");
    printf("main: *heap_ptr = %d\n", *heap_ptr);

    free(heap_ptr);
    heap_ptr = NULL;

    puts("main: allocated memory freed");

    return 0;
}
