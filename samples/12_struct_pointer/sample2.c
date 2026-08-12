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
    Person *ptr = &person;

    printf("sizeof(Person) = %zu\n", sizeof(Person));
    printf("sizeof(ptr)    = %zu\n", sizeof(ptr));

    printf("\nAddress:\n");
    printf("&person = %p\n", (void *)&person);
    printf("ptr     = %p\n", (void *)ptr);
    printf("&ptr    = %p\n", (void *)&ptr);

    printf("\nPerson memory:\n");
    mdump(&person, sizeof(Person));

    printf("\nPointer variable memory:\n");
    mdump(&ptr, sizeof(ptr));

    printf("\nMember access:\n");
    printf("person.age    = %d\n", person.age);
    printf("(*ptr).age    = %d\n", (*ptr).age);
    printf("ptr->age      = %d\n", ptr->age);

    printf("person.grade  = %c\n", person.grade);
    printf("(*ptr).grade  = %c\n", (*ptr).grade);
    printf("ptr->grade    = %c\n", ptr->grade);

    return 0;
}
