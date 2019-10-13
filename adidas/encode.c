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
    
    // 1. read bytes from the input file
    int byteCounter = getNumberOfBytesInFile(input_filename);
    uint8_t originalByteArray[byteCounter];
    readFileInBinary(input_filename, byteCounter, originalByteArray);

    int i;
    for (i = 0; i < byteCounter; i++) {
        printf("Original byte: %ui\n", originalByteArray[i]);
    }

    // 2. split bytes into nibbles and put them in array
    uint8_t byteArray[byteCounter * 2]; // holder for nibbles
    splitIntoNibbles(originalByteArray, byteArray, byteCounter);

    // 3. assigning parity bits here
    for (i = 0; i < byteCounter * 2; i++) {
        byteArray[i] = addParityBits(byteArray[i]);
    }

    // 4. finally, we write newly created bytes to the output file
    writeToFile(byteArray, byteCounter * 2, output_filename);

    return 0;
}

