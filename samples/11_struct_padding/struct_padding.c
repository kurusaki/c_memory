/*
 * struct_padding.c
 *
 * 第11回 パディングを減らす方法とは？
 *
 * 構造体メンバーの並び順を変え、
 * sizeofとmdumpを使って、
 * パディングとメモリ配置の違いを確認します。
 */

#include <stdio.h>
#include "../mdump.h"

struct Sample1 {
    char a;
    int b;
    char c;
};

struct Sample2 {
    int b;
    char a;
    char c;
};

int main(void)
{
    struct Sample1 sample1 = {0};
    struct Sample2 sample2 = {0};

    sample1.a = 0x11;
    sample1.b = 0x22222222;
    sample1.c = 0x33;

    sample2.a = 0x11;
    sample2.b = 0x22222222;
    sample2.c = 0x33;

    printf("sizeof(Sample1) = %zu\n", sizeof(struct Sample1));
    mdump(&sample1, sizeof(sample1));

    printf("\n");

    printf("sizeof(Sample2) = %zu\n", sizeof(struct Sample2));
    mdump(&sample2, sizeof(sample2));

    return 0;
}
