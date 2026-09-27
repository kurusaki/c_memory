#include <stdio.h>

int main(void)
{
    char name[] = "Hello";
    char *ptr = name;

    ptr[0] = 'h';

    printf("name = %s\n", name);
    printf("ptr  = %s\n", ptr);

    return 0;
}
