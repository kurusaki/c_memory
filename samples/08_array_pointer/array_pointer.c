/*
 * array_pointer.c
 *
 * C言語の壁を越えよう！
 * ～メモリの世界から理解するC言語～
 *
 * #8 配列とポインタは同じ？
 *
 * このサンプルでは、配列とポインタの関係について学びます。
 *
 * - a[2] と *(a + 2) の関係
 * - 配列名は先頭要素のアドレスとして扱われる
 * - 配列とポインタの共通点
 * - 配列とポインタの違い
 *
 * YouTube:
 * https://www.youtube.com/@CodeBoostLabo
 *
 * GitHub:
 * https://github.com/kurusaki/c_memory
 */
#include <stdio.h>

int main(void)
{
    int a[] = {10,20,30,40};

    printf("%d\n", a[2]);
    printf("%d\n", *(a + 2));

    return 0;
}

