#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_helper.h"
#include "binary_helper.h"

int main(int argc, char **argv) 
{
    // check if the number of arguments is equal to 3
    if (argc != 3)
    {
        printf("Should have 3 arguments\n");
        return -1;
    }

    /* 
        Get input and output file names from arguments
        and copy them to local variables
    */
    char input_filename[15];
    strcpy (input_filename, argv[1]);
    char output_filename[15];
    strcpy (output_filename, argv[2]);

    // 1. read all bytes from input file
    int counter = getNumberOfBytesInFile(input_filename);
    uint8_t byteArray[counter];
    readFileInBinary(input_filename, counter, byteArray);

    // 2. decode every single nibble 
    int i;
    for (i = 0; i < counter; i++) {
        byteArray[i] = decodeNibble(byteArray[i]);
        printf("Byte: %ui\n", byteArray[i]);
    }  

    // 3. merge pair nibbles into byte
    uint8_t originalArray[counter / 2];
    for (i = 0; i < counter; i+=2) {
        originalArray[i/2] = mergeNibblesIntoByte(byteArray[i], byteArray[i+1]);
        printf("Original byte: %ui\n", originalArray[i/2]);
    }

    // 4. write all bytes to the output file
    writeToFile(originalArray, counter / 2, output_filename);

    return 0;
}