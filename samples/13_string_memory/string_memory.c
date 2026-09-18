#include <stdio.h>
#include "../mdump.h"

int main(void)
{
    char name[] = "Hello";

    /* 終端のヌル文字も含めて、配列全体を確認する。 */
    printf("name = %s\n", name);
    printf("sizeof(name) = %zu\n", sizeof(name));
    mdump(name, sizeof(name));

    /* 3番目の要素を書き換え、文字列の終わりを途中に移す。 */
    name[2] = '\0';

    printf("\nAfter name[2] = '\\0'\n");
    printf("name = %s\n", name);
    printf("sizeof(name) = %zu\n", sizeof(name));
    mdump(name, sizeof(name));

    return 0;
}
