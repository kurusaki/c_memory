#include <stdio.h>
int main(void) {
    int age = 20;

    printf("age = %d\n", age);
    
    printf("%p\n", (void *)&age);

    printf("char : %zu\n", sizeof(char));
    printf("int : %zu\n", sizeof(int));


    
    return 0;
}

