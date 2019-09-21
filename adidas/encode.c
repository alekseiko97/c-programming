#include <stdio.h>
#include "file_helper.h"

int main(int argc, char **argv)
{
    // check if the number of arguments is equal to 3
    if (argc != 2)
    {
        printf("Should have 3 arguments");
        return -1;
    }

    char* input_file = argv[1];
    //char* output_file = argv[2];

    // Read input file
    readBytesFromFile(input_file);
    //writeBytesToFile(output_file);

}

