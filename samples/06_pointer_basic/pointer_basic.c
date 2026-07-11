#include <stdio.h>
#include "../mdump.h"

int main(void)
{
    int num = 100;
    int *ptr = &num;

    printf("num  = %d\n", num);
    printf("&num = %p\n", (void *)&num);
    printf("ptr  = %p\n", (void *)ptr);
    printf("*ptr = %d\n", *ptr);

    printf("\n--- Memory Dump ---\n");

    mdump(&num, sizeof(num));
    mdump(&ptr, sizeof(ptr));

    return 0;
}

