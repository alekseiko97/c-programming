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
    uint8_t msb;
    uint8_t lsb;
    uint8_t byte;
    fp = fopen(argv[1], "rb");  // read in binary mode

    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        return -1;
    }

    int res = fread (&byte, 1, 1, fp);
    int counter = 0;

    while ( res > 0 ) {

        if (counter == 1) {
            counter = 0;
            lsb = byte;
            decodeNibble(&lsb);

            uint8_t originalByte = mergeNibblesIntoByte(msb, lsb);
            printf("Original byte: %ui\n", originalByte);
            writeToFile(originalByte, argv[2]);
        } else {
            msb = byte;
            decodeNibble(&msb);
            counter++;
        }

        // read the next one
        res = fread (&byte, 1, 1, fp);
    }

    // close the stream
    fclose(fp);

    return 0;
}