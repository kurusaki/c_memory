#include <stdio.h>
#include <stdlib.h>

int global_value = 100;
int global_zero;

int main(void)
{
    static int static_value = 200;
    static int static_zero;
    int local_value = 300;
    int *heap_ptr = malloc(sizeof *heap_ptr);

    if (heap_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    *heap_ptr = 400;

    printf("global_value : %p, value = %d\n",
           (void *)&global_value, global_value);
    printf("static_value : %p, value = %d\n",
           (void *)&static_value, static_value);
    printf("global_zero  : %p, value = %d\n",
           (void *)&global_zero, global_zero);
    printf("static_zero  : %p, value = %d\n",
           (void *)&static_zero, static_zero);
    printf("local_value  : %p, value = %d\n",
           (void *)&local_value, local_value);
    printf("heap_ptr     : %p, value = %d\n",
           (void *)heap_ptr, *heap_ptr);
    printf("&heap_ptr    : %p\n", (void *)&heap_ptr);

    free(heap_ptr);
    return 0;
}
