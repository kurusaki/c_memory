/*
 * 02_pointer_loop.c
 *
 * ポインタを使った配列の走査
 *
 * 学ぶこと
 * - p++ を使ったポインタ演算
 * - ポインタで配列を順番に読み取る方法
 * - 添字(array[i])との比較
 * - 配列とポインタの関係
 */
#include <stdio.h>

int main(void)
{
    int array[] = {10, 20, 30, 40, 50};

    printf("添字を使ったループ\n");

    for (int i = 0; i < 5; i++) {
        printf("%d\n", array[i]);
    }

    printf("\nポインタを使ったループ\n");

    int *p = array;

    for (int i = 0; i < 5; i++) {
        printf("%p : %d\n", (void *)p, *p);
        p++;
    }

    return 0;
}

