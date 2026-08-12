#include <stdio.h>
#include "../mdump.h"

typedef struct
{
    int age;
    char grade;
} Person;

int main(void)
{
    Person people[3] = {
        {20, 'A'},
        {30, 'B'},
        {40, 'C'}
    };

    Person *ptr = people;

    printf("sizeof(Person) = %zu\n", sizeof(Person));
    printf("sizeof(people) = %zu\n", sizeof(people));

    printf("\nArray address:\n");
    printf("people     = %p\n", (void *)people);
    printf("&people[0] = %p\n", (void *)&people[0]);
    printf("&people[1] = %p\n", (void *)&people[1]);
    printf("&people[2] = %p\n", (void *)&people[2]);

    printf("\nPeople memory:\n");
    mdump(people, sizeof(people));

    printf("\nPointer access:\n");

    printf("ptr = %p, age = %d, grade = %c\n",
           (void *)ptr, ptr->age, ptr->grade);

    ptr++;

    printf("ptr = %p, age = %d, grade = %c\n",
           (void *)ptr, ptr->age, ptr->grade);

    ptr++;

    printf("ptr = %p, age = %d, grade = %c\n",
           (void *)ptr, ptr->age, ptr->grade);

    return 0;
}
