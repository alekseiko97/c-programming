#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

    srand( time(NULL) );

    char input_filename[15];
    strcpy (input_filename, argv[1]);
    char output_filename[15];
    strcpy (output_filename, argv[2]);

    int counter = getNumberOfBytesInFile(input_filename);

    uint8_t byteArray[counter];

    readFileInBinary(input_filename, counter, byteArray);

    int flipCounter = 0;

    for (int i = 0; i < counter; i++) {

        int isFlipped = rand() % 2;

        if (isFlipped == 1) { // if true
            ++flipCounter;
            printf("To be modified: %ul\n", byteArray[i]);
            byteArray[i] = flipBit(byteArray[i]);
            printf("Modified: %ul\n", byteArray[i]);
            printf("--------------\n");
        } else {
            printf("Skipped byte: %ui\n", byteArray[i]);
            printf("--------------\n");
        }
    }

    writeToFile(byteArray, counter, output_filename);
    printf("\nFlipped %d times\n", flipCounter);
}