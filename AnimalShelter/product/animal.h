#ifndef _ANIMAL_H
#define _ANIMAL_H

typedef enum
{
    Cat = 0,
    Dog = 1,
    GuineaPig = 2,
    Parrot = 3
} SPECIES;


#define MaxNameLength 25

typedef struct
{
    char    Name[MaxNameLength];
    SPECIES Species;
    int     Age;
} ANIMAL;

#endif
