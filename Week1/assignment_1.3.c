#include <stdio.h>
#include "secondFile.h"

int main(void) 
{
    int a;
    a = otherFunction(2,3);
    printf("%d\n", a);
    return a;
}