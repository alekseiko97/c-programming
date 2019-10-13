#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

    srand( time(NULL) );

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

    // 2. flip random bit in a randomly taken byte
    int flipCounter = 0;
    for (int i = 0; i < counter; i++) {

        // decide whether the byte will be flipped or not (true or false)
        int isFlipped = rand() % 2; 

        if (isFlipped == 1) { // true
            ++flipCounter;
            printf("To be modified: %ul\n", byteArray[i]);
            byteArray[i] = flipBit(byteArray[i]);
            printf("Modified: %ul\n", byteArray[i]);
            printf("--------------\n");
        } else { // false
            printf("Skipped byte: %ui\n", byteArray[i]);
            printf("--------------\n");
        }
    }

    // 3. write bytes to the output file
    writeToFile(byteArray, counter, output_filename);
    printf("\nFlipped %d times\n", flipCounter);
}