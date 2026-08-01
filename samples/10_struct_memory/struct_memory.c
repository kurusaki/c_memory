/*
 * struct_memory.c
 *
 * 第10回 構造体はメモリ上でどう並ぶ？
 * ～sizeofが予想より大きい理由～
 */

#include <stdio.h>
#include "../mdump.h"

struct Person {
    char age;
    int score;
};

int main(void)
{
    struct Person person;

    person.age = 20;
    person.score = 100;

    printf("sizeof(Person) = %zu\n", sizeof(struct Person));

    mdump(&person, sizeof(person));

    return 0;
}

