#include <stdio.h>
#include <string.h>
#include "../mdump.h"

int main(void)
{
    char name[] = "Hello";
    const char *ptr = "Hello";

    printf("name = %s\n", name);
    printf("ptr  = %s\n", ptr);
    printf("sizeof(name) = %zu\n", sizeof(name));
    printf("sizeof(ptr)  = %zu\n", sizeof(ptr));
    printf("strlen(name) = %zu\n", strlen(name));
    printf("strlen(ptr)  = %zu\n", strlen(ptr));

    printf("\nAddress:\n");
    printf("name = %p\n", (void *)name);
    printf("ptr  = %p\n", (void *)ptr);
    printf("&ptr = %p\n", (void *)&ptr);

    printf("\nArray memory:\n");
    mdump(name, sizeof(name));
    printf("\nPointer variable memory:\n");
    mdump(&ptr, sizeof(ptr));
    printf("\nString pointed to by ptr:\n");
    mdump(ptr, strlen(ptr) + 1);

    name[0] = 'h';
    ptr = "World";

    printf("\nAfter changes:\n");
    printf("name = %s\n", name);
    printf("ptr  = %s\n", ptr);

    return 0;
}
