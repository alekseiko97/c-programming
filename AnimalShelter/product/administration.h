#ifndef _ADMINISTRATION_H
#define _ADMINISTRATION_H

#include "animal.h"

int size; // current size

// specify your own functions
void createDummyAnimals(ANIMAL animalArray[]);
int addAnimal(ANIMAL *animalPtr, ANIMAL animalArray[]);
void showAnimals(ANIMAL animalArray[]);
int removeAnimal(char name[], ANIMAL animalArray[]);
int findAnimalByName(char name[], ANIMAL animalArray[]);
int countAnimals(ANIMAL animalArray[]);
int countSpacesLeft(ANIMAL animalArray[]);

#endif
