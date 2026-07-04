#include <stdio.h>
#include "mdump.h"

int main(void) {
    char  c = 20;
    short s = 20;
    int   i = 20;
    long  l = 20;

    printf("===== char  (20) : 1バイト =====\n");
    mdump(&c, sizeof(c));

    printf("===== short (20) : 2バイト =====\n");
    mdump(&s, sizeof(s));

    printf("===== int   (20) : 4バイト =====\n");
    mdump(&i, sizeof(i));

    printf("===== long  (20) : 8バイト =====\n");
    mdump(&l, sizeof(l));

    return 0;
}


