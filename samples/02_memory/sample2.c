#include <stdio.h>

int main(void) 
{
    int age = 20;

    printf("age = %d\n", age);
    printf("address = %p\n", (void *)&age);

    return 0;
}