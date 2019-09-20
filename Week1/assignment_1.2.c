#include <stdio.h>

int main(void) 
{
    int x = 7;
    int* px1;
    int* px2;

    px1 = px2 = &x;
    *px1 = 10;

    printf("%d\n", *px2);
}