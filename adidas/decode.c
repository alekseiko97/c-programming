#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_helper.h"
#include "binary_helper.h"

int main(int argc, char **argv) {

    //check if the number of arguments is equal to 3
    if (argc != 3)
    {
        printf("Should have 3 arguments\n");
        return -1;
    }

    char input_filename[15];
    strcpy (input_filename, argv[1]);
    char output_filename[15];
    strcpy (output_filename, argv[2]);

    int counter = getNumberOfBytesInFile(input_filename);

    uint8_t byteArray[counter];

    readFileInBinary(input_filename, counter, byteArray);
    int j;
    for (j = 0; j < counter; j++) {
        printf("%ui\n", byteArray[j]);
    }

    for (int i = 0; i < counter; i++) {
        byteArray[i] = decodeNibble(byteArray[i]);
        printf("Decoded: %ui\n", byteArray[i]);
    }  

    uint8_t originalArray[counter / 2];

    int i;
    for (i = 0; i < counter; i+=2) {
        originalArray[i/2] = mergeNibblesIntoByte(byteArray[i], byteArray[i+1]);
        printf("Original byte: %ui\n", originalArray[i/2]);
    }

    writeToFile(originalArray, counter / 2, output_filename);
    return 0;
}