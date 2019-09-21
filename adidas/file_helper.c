#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readBytesFromFile(char file_name[])
{
    char ch;
    FILE *fp;
    int res;

    fp = fopen(file_name, "r");  // read mode

    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        return;
    }

    res = fread(&ch, sizeof(char), 1, fp);

    uint8_t out[40];
    uint8_t c = 0;
    int i = 0;

    do {
        c = fgetc(fp);

        if (feof(fp))
        {
            break;
        }

        res = fread(&ch, sizeof(char), 1, fp);
        printf("%с is %u", ch, c);
        out[i] = c;
        i++;
    } while (1);

    printf("\n");
    fclose(fp);

}
