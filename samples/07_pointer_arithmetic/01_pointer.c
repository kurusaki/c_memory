/*
 * 01_pointer.c
 *
 * ポインタ演算の基本
 *
 * 学ぶこと
 * - ポインタ演算とは何か
 * - p + 1 が型1個分進む理由
 * - sizeof() と型のサイズ
 * - int * が4バイト進む理由
 */

#include <stdio.h>

int main(void)
{
    int array[] = {10, 20, 30, 40, 50};

    int *p = array;

    printf("sizeof(int) = %zu\n", sizeof(int));

    printf("p     = %p\n", (void *)p);
    printf("p + 1 = %p\n", (void *)(p + 1));
    printf("p + 2 = %p\n", (void *)(p + 2));
    printf("p + 3 = %p\n", (void *)(p + 3));
    printf("p + 4 = %p\n", (void *)(p + 4));

    return 0;
}

