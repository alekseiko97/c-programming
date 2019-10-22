#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "binary_helper.h"

int main(int argc, char **argv) 
{
    // check if the number of arguments is equal to 3
    if (argc != 3)
    {
        printf("Should have 3 arguments\n");
        return -1;
    }

    srand( time(NULL) );

    FILE *fp;
    uint8_t byte;
    fp = fopen(argv[1], "rb");  // read in binary mode

    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        return -1;
    }

    int res = fread (&byte, 1, 1, fp);

    int flipCounter = 0;
    while ( res > 0 ) {

        // decide whether the byte will be flipped or not (true or false)
        int isFlipped = rand() % 2;

        if (isFlipped == 1) { // true
            flipBit(&byte);
            printf("Flipped\n");
            flipCounter++;
        } else {
            printf("Not flipped\n");
        } 

        writeToFile(byte, argv[2]);

        // read the next one
        res = fread (&byte, 1, 1, fp);
    }

   // printf("Flipped %d times\n", flipCounter);

    // close the stream
    fclose(fp);

    return 0;
}