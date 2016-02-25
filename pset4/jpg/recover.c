/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    if (file) {
            while ((c = getc(file)) != EOF)
                        putchar(c);
                fclose(file);
    }
}
