#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_helper.h"
#include "binary_helper.h"

int main(int argc, char **argv)
{
    //check if the number of arguments is equal to 3
    if (argc != 3)
    {
        printf("Should have 3 arguments\n");
        return -1;
    }

    char input_filename[15];
    strcpy (input_filename ,argv[1]);
    char output_filename[15];
    strcpy (output_filename, argv[2]);
    

    
    int byteCounter = getNumberOfBytesInFile(input_filename);
    uint8_t output[byteCounter];
    readFileInBinary(input_filename, byteCounter, output);

    int j;
    for (j = 0; j < byteCounter; j++) {
        printf("Original byte: %ui\n", output[j]);
    }


    uint8_t byteArray[byteCounter * 2]; // holder for nibbles
    splitIntoNibbles(output, byteArray, byteCounter);

    uint8_t *nibblePointer;

    // assigning parity bits here
    int i;
    for (i = 0; i < byteCounter * 2; i++) {
        nibblePointer = &byteArray[i];
        byteArray[i] = addParityBits(nibblePointer);
    }

    // finally, we write bytes to the output file
    writeToFile(byteArray, byteCounter * 2, output_filename);

    return 0;
}

