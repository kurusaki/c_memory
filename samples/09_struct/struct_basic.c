/*
 * struct_basic.c
 *
 * 第9回 構造体とは何か？
 * ～関連するデータを一つにまとめよう～
 */

#include <stdio.h>

struct Person {
    char name[32];
    int age;
    double height;
};

int main(void)
{
    struct Person person;

    snprintf(person.name, sizeof(person.name), "Taro");
    person.age = 20;
    person.height = 170.5;

    printf("名前 : %s\n", person.name);
    printf("年齢 : %d\n", person.age);
    printf("身長 : %.1f cm\n", person.height);

    return 0;
}


