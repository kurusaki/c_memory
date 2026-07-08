#include <stdio.h>
#include "../mdump.h"

int main(void)
{
    int data[5] = {10, 20, 30, 40, 50};

    mdump(data, sizeof(data));

    printf("&data[0] = %p\n", &data[0]);
    printf("&data[1] = %p\n", &data[1]);
    printf("&data[2] = %p\n", &data[2]);
    printf("&data[3] = %p\n", &data[3]);
    printf("&data[4] = %p\n", &data[4]);

    return 0;
}



