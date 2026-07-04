#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

void mdump(void *addr, size_t size)
{
    unsigned char *p = (unsigned char *)addr;

    for (size_t i = 0; i < size; i += 16) {

        printf("%p : ", p + i);

        /* HEX表示 */
        for (size_t j = 0; j < 16; j++) {

            if (i + j < size) {
                printf("%02X ", p[i + j]);
            } else {
                printf("   ");
            }
        }

        printf(" ");

        /* ASCII表示 */
        for (size_t j = 0; j < 16 && i + j < size; j++) {

            unsigned char c = p[i + j];

            if (isprint(c)) {
                printf("%c", c);
            } else {
                printf(".");
            }
        }

        printf("\n");
    }
}