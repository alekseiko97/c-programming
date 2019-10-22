#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_helper.h"

int main(int argc, char **argv)
{
    // check if the number of arguments is equal to 3
    if (argc != 3)
    {
        printf("Should have 3 arguments\n");
        return -1;
    }

    FILE *fp;
    uint8_t byte;
    fp = fopen(argv[1], "rb");  // read in binary mode

    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        return -1;
    }

    int res = fread (&byte, 1, 1, fp);

    while ( res > 0 ) { // while there is something to read

        printf("Original byte: %ui\n", byte);

        uint8_t nibbles[2]; // nibbles will go here
        splitIntoNibbles(byte, nibbles);

        addParityBits(&nibbles[0]);
        addParityBits(&nibbles[1]);

        writeToFile(nibbles[0], argv[2]);
        writeToFile(nibbles[1], argv[2]);

        // read the next one
        res = fread (&byte, 1, 1, fp);
    }

    // close the stream
    fclose(fp);

    return 0;
}

