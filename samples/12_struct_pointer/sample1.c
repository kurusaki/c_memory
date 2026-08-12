#include <stdio.h>
#include "../mdump.h"

typedef struct
{
    int age;
    char grade;
} Person;

int main(void)
{
    Person person = {20, 'A'};

    printf("sizeof(Person) = %zu\n", sizeof(Person));
    printf("&person        = %p\n", (void *)&person);
    printf("&person.age    = %p\n", (void *)&person.age);
    printf("&person.grade  = %p\n", (void *)&person.grade);

    printf("\nPerson memory:\n");
    mdump(&person, sizeof(Person));

    return 0;
}
