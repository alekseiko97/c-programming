#ifndef _FILEHELPER_H
#define _FILEHELPER_H

#define MAX 100;

int getNumberOfBytesInFile(char* filename);
void readFileInBinary(char* filename, int bytesCounter, uint8_t output[]);
void writeToFile(uint8_t byteArray[], int size, const char output_filename[]);

#endif