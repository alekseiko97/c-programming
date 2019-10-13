#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_helper.h"

/*
    This function counts and returns how many bytes are in the file
*/

int getNumberOfBytesInFile(char* filename)
{
    FILE* fp;
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return -1;
    }

    int nrOfBytes = 0;
    uint8_t c = 0;
    do 
    {
        c = fgetc(fp); // read every single char

        // if reached the end of the file
        if (feof(fp))
        {
            break;
        }
        nrOfBytes++;
    } while (1);

    return nrOfBytes;
}

/*
    This function reads input file in binary mode and writes the content in output array
*/

void readFileInBinary(char* filename, int bytesCounter, uint8_t output[])
{
    FILE *fp;
    uint8_t c;
    fp = fopen(filename, "rb");  // read in binary mode

    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        return;
    }

    int i = 0;
    while ( i < bytesCounter) {
        //fread(buffer, sizeof(uint8_t), 1, fp);
        c = fgetc(fp);
       // printf("%ui\n", c);
        output[i] = c;
        i++;
    }

    fclose(fp);
}

void writeToFile(uint8_t byteArray[], int size, const char filename[]) {
    FILE* fp;
    fp = fopen(filename, "wb"); // write in binary

    if (fp == NULL) {
        printf("Error while opening the file.\n");
        return;
    }

    int i;
    for (i = 0; i < size; i++) {
        fwrite(&byteArray[i], sizeof(byteArray[0]), 1, fp);
    }
    
    fclose(fp);
}